#include "Rope/Config/FloatConfig.hpp"

#define INFO_PREFIX "Config:"

namespace Rope
{
    FloatConfig::FloatConfig(const std::string& name, const float defaultValue) : name(name), defaultValue(defaultValue)
    {
        // char numberArray[20];

        // // Verifica se o arquivo existe
        // if (!LittleFS.exists(("/" + name).c_str()))
        // {
            
        //     // Se não existir, grava o valor padrão
        //     File file = LittleFS.open(("/" + name).c_str(), "w", true);
        //     if (file)
        //     {
        //         snprintf(numberArray, sizeof(numberArray), "%f", defaultValue);
        //         file.print(numberArray);
        //         file.close();
        //     }
        // }
    }

    void FloatConfig::init() const
    {
        char numberArray[20];

        // Verifica se o arquivo existe
        // if (!LittleFS.exists(("/" + name).c_str()))
        // {
            
        //     // Se não existir, grava o valor padrão
        //     File file = LittleFS.open(("/" + name).c_str(), "w", true);
        //     if (file)
        //     {
        //         snprintf(numberArray, sizeof(numberArray), "%f", defaultValue);
        //         file.print(numberArray);
        //         file.close();
        //     }
        // }
    }

    float FloatConfig::get() const
    {
        return this->defaultValue;
        // File file = LittleFS.open(("/" + name).c_str(), "r");
        // if (file)
        // {
        //     String value = file.readString();
        //     file.close();
        //     return value.toFloat();
        // }
        // else
        // {
        //     return defaultValue;
        // }
    }

    void FloatConfig::set(const float value)
    {
        this->defaultValue = value;
        // char numberArray[20];
        // File file = LittleFS.open(("/" + name).c_str(), "w", true);
        // if (file)
        // {
        //     snprintf(numberArray, sizeof(numberArray), "%f", value);
        //     file.print(numberArray);
        //     file.close();
        // }
    }
}