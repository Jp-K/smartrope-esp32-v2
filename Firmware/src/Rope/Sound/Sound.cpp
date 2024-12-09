#include "Rope/Sound/Sound.hpp"

#include <Arduino.h>

#include "Rope/RopeToy.hpp"
#include "Rope/IoT/Events/SoundTunedEvent.hpp"
#include "Rope/IoT/Events/SoundPlaybackStartedEvent.hpp"
#include "Rope/IoT/Events/SoundPlaybackFinishedEvent.hpp"

namespace Rope
{
    Sound::Sound(RopeToy& rope, uint8_t pin, int8_t pitchVariation) : NamedEntity("Sound"),
        rope(rope),
        pin(pin),
        pitchVariation(pitchVariation)
    {
        pinMode(pin, OUTPUT);
    }

    bool Sound::isOn() const
    {
        return rope.config.soundEnabled.get();
    }

    bool Sound::isOff() const
    {
        return !isOn();
    }

    bool Sound::isPlaying() const
    {
        return playing;
    }

    void Sound::turnOn(const std::string& requester)
    {
        if (isOff())
        {
            rope.config.soundEnabled.set(true);
            notifySoundTuned(requester);
        }
    }

    void Sound::turnOff(const std::string& requester)
    {
        if (isOn())
        {
            stop(requester);

            rope.config.soundEnabled.set(false);
            notifySoundTuned(requester);
        }
    }

    bool Sound::canPlay(const std::string& melody, const PlaybackParameters& parameters) const
    {
        if (isOff())
        {
            // h4pUserEvent("%s: sound is off, will not play the melody", getName().c_str());
            return false;
        }

        if (parameters.getVolume() == 0)
        {
            // h4pUserEvent("%s: volume is 0, will not play the melody", getName().c_str());
            return false;
        }

        if (melody.empty())
        {
            // h4pUserEvent("%s: melody is null or empty", getName().c_str());
            return false;
        }

        if (playing)
        {
            // h4pUserEvent("%s: cannot play, a melody is already playing", getName().c_str());
            return false;
        }

        return true;
    }

    bool Sound::cannotPlay(const std::string& melody, const PlaybackParameters& parameters) const
    {
        return !canPlay(melody, parameters);
    }

    PlaybackParameters Sound::getDefaultPlaybackParameters() const
    {
        PlaybackParameters parameters(rope);

        parameters.setRepetitions(1);
        parameters.setTempo(rope.config.soundTempo.get());
        parameters.setVolume(rope.config.soundVolume.get());
        parameters.setTransposition(rope.config.soundTransposition.get());

        return parameters;
    }

    void Sound::setDefaultPlaybackParameters(const std::string& requester, const PlaybackParameters& parameters)
    {
        rope.config.soundTempo.set(parameters.getTempo());
        rope.config.soundVolume.set(parameters.getVolume());
        rope.config.soundTransposition.set(parameters.getTransposition());

        notifySoundTuned(requester);
    }

    void Sound::stop(const std::string& requester)
    {
        if (playing)
        {
            stopRequester = requester;

            if (soundTask)
            {
                // h4.finishNow(soundTask);
                soundTask = nullptr;
            }
        }
    }

    float Sound::getFrequency(const Note note, const uint8_t octave) const
    {
        const uint8_t distanceFromC0 = (12 * octave) + static_cast<uint8_t>(note);

        return 16.35f * pow(1.059463094359f, distanceFromC0);
    }

    void Sound::applyPicthVariation(Note &note, uint8_t &octave, const int8_t variation) const
    {
        uint8_t distanceFromC0 = (12 * octave) + static_cast<uint8_t>(note) + variation;

        octave = distanceFromC0 / 12;
        note = static_cast<Note>(distanceFromC0 % 12);
    }

    void Sound::setPitchVariation(const int8_t pitch)
    {
        pitchVariation = pitch;
    }

    void Sound::play(const std::string& requester, Note note, uint8_t octave, const float duration, const float pause, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        // Note note, uint8_t octave, const float duration, const float pause

        float frequency = getFrequency(note, octave);
        play(requester, frequency, duration, pause, startCallback, finishCallback);
    }

    void Sound::play(const std::string& requester, float frequency, const float duration, const float pause, AsyncStartCallback startCallback, AsyncFinishCallback finishCallback)
    {
        // auto parameters = getDefaultPlaybackParameters();
        playing = true;
        stopRequester.clear();

        if (startCallback)
        {
            AsyncActionStart result;
            result.setExecutionRequester(requester);
            startCallback(result);
        }

        // Notify and starts the first playback immediately
        // notifyPlaybackStarted(requester, melody, parameters, playbackIndex);
        // h4vox.play(notes, parameters.getTransposition());
        // inicio toque
        uint8_t distanceFromC0 = round(log10(frequency / 16.35f) / log10(1.059463094359f));
        uint8_t noteValue = distanceFromC0 % 12;
        uint8_t octave = (distanceFromC0 - noteValue) / 12;
        Note note = (Note) noteValue;

        applyPicthVariation(note, octave, pitchVariation); // Need to calculate
        
        frequency = getFrequency(note, octave);

        ledcSetup(0, round(frequency), 8); // Configura o canal 0 com uma frequência e resolução de 8 bits
        ledcAttachPin(pin, 0);  // Associa o canal 0 ao pino do buzzer
        tone(pin, round(frequency));
        if (xTaskGetCurrentTaskHandle() != NULL) {
            vTaskDelay(pdMS_TO_TICKS(roundf(duration * 1000)));
        } else {
            delay(roundf(duration * 1000));
        }
        
        noTone(pin);

        if (pause > 0.0f)
        {
            // delay(roundf(duration * 1000));
            if (xTaskGetCurrentTaskHandle() != NULL) {
                vTaskDelay(pdMS_TO_TICKS(roundf(pause * 1000)));
            } else {
                delay(roundf(pause * 1000));
            }
        }
        // fim toque

        if (finishCallback)
        {
            AsyncActionFinish result;
            result.setExecutionRequester(requester);
            result.setFinishMode(stopRequester.empty() ? AsyncFinishMode::Normal : AsyncFinishMode::Abortion);
            result.setAbortionRequester(stopRequester);
            finishCallback(result);
            //rope.program.execute(Event::Origin::Rope, nullptr, nullptr);
        }
    }

    void Sound::notifyPlaybackStarted(const std::string& requester, const std::string& melody, const PlaybackParameters& parameters, uint32_t index) const
    {
        SoundPlaybackStartedEvent event(requester, melody, parameters, index);
        rope.IoT.notifyEvent(&event);
    }

    void Sound::notifyPlaybackFinished(const std::string& requester, const std::string& melody, const PlaybackParameters& parameters, uint32_t index) const
    {
        const std::string finishRequester = stopRequester.empty() ? requester : stopRequester;
        bool wasInterrupted = !stopRequester.empty();

        SoundPlaybackFinishedEvent event(finishRequester, melody, parameters, index, wasInterrupted);
        rope.IoT.notifyEvent(&event);
    }

    void Sound::notifySoundTuned(const std::string& requester) const
    {
        PlaybackParameters parameters = getDefaultPlaybackParameters();

        SoundTunedEvent event(requester, parameters, isOn());
        rope.IoT.notifyEvent(&event);
    }
} // namespace Rope