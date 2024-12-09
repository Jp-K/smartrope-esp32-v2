#ifndef ROPE_IOT_COMMAND_HPP
#define ROPE_IOT_COMMAND_HPP

#include <string>

#include <ArduinoJson.h>

#include "Rope/Common/NamedEntity.hpp"

namespace Rope
{
    class RopeToy;
    class Command : public NamedEntity
    {
    protected:
        RopeToy& rope;

    public:
        Command(const std::string& name, RopeToy& rope);

        virtual bool execute(const std::string& requester, const JsonObject& parameters) const = 0;
    };
}

#endif // ROPE_IOT_COMMAND_HPP