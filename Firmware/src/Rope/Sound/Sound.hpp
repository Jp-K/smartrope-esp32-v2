#ifndef ROPE_SOUND_HPP
#define ROPE_SOUND_HPP

#include <stdint.h>
#include <string>

#include "Note.hpp"

#include "Rope/Common/NamedEntity.hpp"
#include "Rope/Sound/PlaybackParameters.hpp"
#include "Rope/Async/Async.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace Rope
{
  class RopeToy;
  class Sound : public NamedEntity
  {
  private:
    RopeToy& rope;

    TaskHandle_t soundTask;

    uint8_t pin;
    int8_t pitchVariation;

    bool playing = false;

    uint32_t playbackIndex;
    std::string stopRequester;

    bool canPlay(const std::string& melody, const PlaybackParameters& parameters) const;
    bool cannotPlay(const std::string& melody, const PlaybackParameters& parameters) const;

    float getFrequency(const Note note, const uint8_t octave) const;
    void applyPicthVariation(Note &note, uint8_t &octave, const int8_t variation) const;

    void notifySoundTuned(const std::string& requester) const;
    void notifyPlaybackStarted(const std::string& requester, const std::string& melody, const PlaybackParameters& parameters, uint32_t index) const;
    void notifyPlaybackFinished(const std::string& requester, const std::string& melody, const PlaybackParameters& parameters, uint32_t index) const;

  public:

    void setPitchVariation(const int8_t pitch);

    Sound(RopeToy& rope, uint8_t pin, int8_t pitchVariation);

    PlaybackParameters getDefaultPlaybackParameters() const;
    void setDefaultPlaybackParameters(const std::string& requester, const PlaybackParameters& parameters);

    void turnOn(const std::string& requester);
    void turnOff(const std::string& requester);

    bool isOn() const;
    bool isOff() const;
    bool isPlaying() const;

    void play(const std::string& requester, Note note, uint8_t octave, const float duration, const float pause, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);
    void play(const std::string& requester, float frequency, const float duration, const float pause, AsyncStartCallback startCallback = nullptr, AsyncFinishCallback finishCallback = nullptr);

    void stop(const std::string& requester);

  };

} // namespace Rope

#endif // ROPE_SOUND_HPP