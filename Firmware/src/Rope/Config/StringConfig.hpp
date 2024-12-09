#ifndef ROPE_STRING_CONFIG
#define ROPE_STRING_CONFIG

#include <string>
// #include <LittleFS.h>

namespace Rope
{
    class StringConfig
    {
    private:

        const std::string name;
        std::string defaultValue;

    public:
        StringConfig(const std::string& name, const std::string& defaultValue);

        std::string get() const;
        void init() const;
        void set(const std::string& value);
    };
}


#endif // ROPE_STRING_CONFIG