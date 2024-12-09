#include "Rope/IoT/Event.hpp"

namespace Rope
{
    const std::string Event::Origin::Rope = "ROPE";
    const std::string Event::Origin::User = "USER";

    Event::Event(const std::string& name, const std::string& origin) : NamedEntity(name), origin(origin)
    {
        id = micros();
        timestamp = millis();
    }

    unsigned long Event::getId() const
    {
        return id;
    }

    unsigned long Event::getTimestamp() const
    {
        return timestamp;
    }

    const std::string& Event::getOrigin() const
    {
        return origin;
    }
}