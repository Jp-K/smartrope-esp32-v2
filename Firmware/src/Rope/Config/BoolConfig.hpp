#ifndef ROPE_BOOL_CONFIG
#define ROPE_BOOL_CONFIG

#include <string>
// #include <LittleFS.h>
namespace Rope
{
    class BoolConfig
    {
    private:

        std::string name;
        bool defaultValue;

    public:
        BoolConfig(const std::string& name, bool defaultValue);

        bool get() const;
        void init() const;
        void set(bool value);
    };
}


#endif // ROPE_BOOL_CONFIG