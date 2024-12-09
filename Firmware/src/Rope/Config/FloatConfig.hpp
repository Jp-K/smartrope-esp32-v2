#ifndef ROPE_FLOAT_CONFIG
#define ROPE_FLOAT_CONFIG

#include <string>
// #include <LittleFS.h>

namespace Rope
{
    class FloatConfig
    {
    private:

        const std::string name;
        float defaultValue;

    public:
        FloatConfig(const std::string& name, const float defaultValue);

        float get() const;
        void init() const;
        void set(const float value);
    };
}


#endif // ROPE_FLOAT_CONFIG