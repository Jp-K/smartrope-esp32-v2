#include "Rope/IoT/Command.hpp"

namespace Rope
{
    Command::Command(const std::string& name, RopeToy& rope) : NamedEntity(name), rope(rope)
    {

    }
}