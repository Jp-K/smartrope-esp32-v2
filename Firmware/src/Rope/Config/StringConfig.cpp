#include "Rope/Config/StringConfig.hpp"

#define INFO_PREFIX "Config:"

namespace Rope
{
    StringConfig::StringConfig(const std::string& name, const std::string& defaultValue) : name(name), defaultValue(defaultValue)
    {
    }

    void StringConfig::init() const
    {
        // Verifica se o arquivo existe
        // if (!LittleFS.exists(("/" + name).c_str()))
        // {
        //     // Se não existir, grava o valor padrão
        //     File file = LittleFS.open(("/" + name).c_str(), "w", true);
        //     if (file)
        //     {
        //         file.print(defaultValue.c_str());
        //         file.close();
        //     }
        // }
    }

    std::string StringConfig::get() const
    {
        return this->defaultValue;
        // File file = LittleFS.open(("/" + name).c_str(), "r");
        // if (file)
        // {
        //     String value = file.readString();
        //     file.close();
        //     return value.c_str();
        // }
        // else
        // {
        //     return defaultValue;
        // }
    }

    void StringConfig::set(const std::string& value)
    {
        this->defaultValue = value;
        // return;
        // File file = LittleFS.open(("/" + name).c_str(), "w", true);
        // if (file)
        // {
        //     file.print(value.c_str());
        //     file.close();
        // }
    }
}