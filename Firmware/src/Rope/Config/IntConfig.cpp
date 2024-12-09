#include "Rope/Config/IntConfig.hpp"


#define INFO_PREFIX "Config:"

namespace Rope
{
    IntConfig::IntConfig(const std::string& name, const int defaultValue) : name(name), defaultValue(defaultValue)
    {
    }

    void IntConfig::init() const
    {
        char numberArray[20];

        // Verifica se o arquivo existe
        // if (!LittleFS.exists(("/" + name).c_str()))
        // {
        //     // Se não existir, grava o valor padrão
        //     File file = LittleFS.open(("/" + name).c_str(), "w", true);
        //     if (file)
        //     {
        //         snprintf(numberArray, sizeof(numberArray), "%d", defaultValue ? defaultValue : 0);
        //         file.print(numberArray);
        //         file.close();
        //     }
        // }
    }

    int IntConfig::get() const
    {
        return this->defaultValue;
        // File file = LittleFS.open(("/" + name).c_str(), "r");
        // if (file)
        // {
        //     String value = file.readString();
        //     file.close();
        //     return value.toInt();
        // }
        // else
        // {
        //     return defaultValue;
        // }
    }

    void IntConfig::set(const int value)
    {
        this->defaultValue = value;
        // return;
        // char numberArray[20];
        // File file = LittleFS.open(("/" + name).c_str(), "w", true);
        // if (file)
        // {
        //     snprintf(numberArray, sizeof(numberArray), "%d", value ? value : 0);
        //     file.print(numberArray);
        //     file.close();
        // }
    }
}