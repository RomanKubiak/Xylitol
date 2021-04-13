//
// Created by atom on 04.04.2021.
//

#ifndef XYLITOL_SETTING_H
#define XYLITOL_SETTING_H
#include <Audio.h>
#include <AudioControl.h>
#include <string>
#include <vector>
#include <functional>

namespace Xylitol {
    enum class ValueType {
        Integer,
        Float,
        Boolean,
        Custom,
        Action
    };
    class Settings;
    class Setting {
    public:
        Setting(const uint8_t _groupIndex = 0,
                const std::string &_displayString = "",
                const double _value = 0.0,
                const double _min = 0.0,
                const double _max = 1.0,
                std::function<void(const double)> _callback = [](const double) {});

        Setting(const uint8_t _groupIndex = 0,
                const std::string &_displayString = "",
                const bool _value = true,
                std::function<void(const double)> _callback = [](const double) {});

        Setting(const uint8_t _groupIndex = 0,
                const std::string &_displayString = "",
                const std::vector <std::string> &_choices = {},
                const double _choiceIndex = 0,
                std::function<void(const double)> _callback = [](const double) {});

        Setting(const uint8_t _groupIndex = 0,
                const std::string &_displayString = "",
                std::function<void(const double)> _callback = [](const double) {},
                const bool isAction = true);

        void operator++(int);

        void operator--(int);

        const double getValue() const { return value; }
        void setValue(const double newValue);
        const std::string getDisplayString() const { return displayString; }
        const std::string getValueString() const;
        const Xylitol::ValueType getType() const { return valueType; }
        void exec();
    private:
        const uint8_t groupIndex;
        const std::string displayString;
        double value;
        const double minValue = 0;
        const double maxValue = 255;
        const std::vector <std::string> choices;
        std::function<void(const double)> callback;
        const ValueType valueType = ValueType::Integer;
    };

}
#endif //XYLITOL_SETTING_H
