#include "Rope/Common/NamedEntity.hpp"


namespace Rope
{
    NamedEntity::NamedEntity(const std::string& name) : name(name)
    {

    }

    const std::string& NamedEntity::getName() const
    {
        return name;
    }
}