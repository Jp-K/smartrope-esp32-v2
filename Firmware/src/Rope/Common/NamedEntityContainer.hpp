#ifndef ROPE_NAMED_ENTITY_CONTAINER
#define ROPE_NAMED_ENTITY_CONTAINER

#include <vector>
#include <string>

#include "Rope/Common/NamedEntity.hpp"

namespace Rope
{
    template <class T>
    class NamedEntityContainer : public NamedEntity
    {
    private:
        std::vector<NamedEntity*> entities;

    protected:
        virtual void addEntity(T& entity) final;

    public:
        NamedEntityContainer(const std::string& name);

        virtual std::vector<T*> all() const final;
        virtual T* withName(const std::string& name) const final;
    };

    template <class T>
    NamedEntityContainer<T>::NamedEntityContainer(const std::string& name) : NamedEntity(name)
    {
        //h4pUserEvent("%s: constructing", name.c_str());
    }

    template <class T>
    std::vector<T*> NamedEntityContainer<T>::all() const
    {
        std::vector<T*> result;
        
        for (auto entity : entities)
        {
            result.push_back((T*) entity);
        }
        
        return result;
    }

    template <class T>
    T* NamedEntityContainer<T>::withName(const std::string& name) const
    {
        for (auto entity : entities)
        {
            if (entity->getName() == name)
            {
                return (T*)entity;
            }
        }

        return nullptr;
    }

    template <class T>
    void NamedEntityContainer<T>::addEntity(T& entity)
    {
        entities.push_back(&entity);
    }
}

#endif // ROPE_NAMED_ENTITY_CONTAINER