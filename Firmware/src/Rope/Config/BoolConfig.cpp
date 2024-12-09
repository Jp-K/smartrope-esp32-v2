#include "Rope/Config/BoolConfig.hpp"

#define INFO_PREFIX "Config:"

namespace Rope
{
    BoolConfig::BoolConfig(const std::string& name, bool defaultValue) : name(name), defaultValue(defaultValue)
    {
    }

    void BoolConfig::init() const
    {
        // Verifica se o arquivo existe
        // if (!LittleFS.exists(("/" + name).c_str()))
        // {
        //     // Se não existir, grava o valor padrão
        //     File file = LittleFS.open(("/" + name).c_str(), "w", true);
        //     if (file)
        //     {
        //         file.print(defaultValue ? "1" : "0");
        //         file.close();
        //     }
        // }
    }

    bool BoolConfig::get() const
    {
        return this->defaultValue;
        // File file = LittleFS.open(("/" + name).c_str(), "r");
        // if (file)
        // {
        //     String value = file.readString();
        //     file.close();
        //     return value == "1";
        // }
        // else
        // {
        //     return defaultValue;
        // }
    }

    void BoolConfig::set(bool value)
    {
        this->defaultValue = value;
        // File file = LittleFS.open(("/" + name).c_str(), "w", true);
        // if (file)
        // {
        //     file.print(value ? "1" : "0");
        //     file.close();
        // }
    }
}