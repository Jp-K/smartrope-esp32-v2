#ifndef ROPE_INT_CONFIG
#define ROPE_INT_CONFIG

#include <string>
// #include <LittleFS.h>

namespace Rope
{
    class IntConfig
    {
    private:

        const std::string name;
        int defaultValue;

    public:
        IntConfig(const std::string& name, const int defaultValue);

        int get() const;
        void init() const;
        void set(const int value);
    };
}


#endif // ROPE_INT_CONFIG