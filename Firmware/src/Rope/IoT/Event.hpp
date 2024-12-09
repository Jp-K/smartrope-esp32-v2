#ifndef ROPE_IOT_EVENT
#define ROPE_IOT_EVENT

#include <string>
#include <ArduinoJson.h>

#include "Rope/Common/NamedEntity.hpp"

namespace Rope
{
    class Event : public NamedEntity
    {
    private:
        unsigned long id;
        unsigned long timestamp;
        std::string origin;

    public:
        class Origin
        {
        public:
            static const std::string Rope;
            static const std::string User;
        };

        Event(const std::string& name, const std::string& origin);

        virtual unsigned long getId() const final;
        virtual unsigned long getTimestamp() const final;
        virtual const std::string& getOrigin() const final;
        virtual void fillData(const JsonObject& data) const = 0;
    };
}

#endif // ROPE_IOT_EVENT