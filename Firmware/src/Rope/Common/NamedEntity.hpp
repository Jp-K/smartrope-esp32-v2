#ifndef ROPE_NAMED_ENTITY
#define ROPE_NAMED_ENTITY

#include <string>

namespace Rope
{
    class NamedEntity
    {
    private:
        std::string name;

    public:
        NamedEntity(const std::string& name);

        virtual const std::string& getName() const final;
    };
}

#endif // ROPE_NAMED_ENTITY