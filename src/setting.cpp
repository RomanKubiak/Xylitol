//
// Created by atom on 04.04.2021.
//

#include "setting.h"

using namespace Xylitol;

Setting::Setting(const uint8_t _groupIndex, const std::string &_displayString,
                 const double _value,
                 const double _min,
                 const double _max,
                 std::function<void(const double)> _callback)
        : groupIndex(_groupIndex), displayString(_displayString), value(_value), minValue(_min), maxValue(_max),
          callback(_callback), valueType(ValueType::Float) {}

Setting::Setting(const uint8_t _groupIndex, const std::string &_displayString,
                 const bool _value,
                 std::function<void(const double)> _callback)
        : groupIndex(_groupIndex), displayString(_displayString), value(_value), callback(_callback),
          valueType(ValueType::Boolean) {}

Setting::Setting(const uint8_t _groupIndex, const std::string &_displayString,
                 const std::vector<std::string> &_choices,
                 const double _choiceIndex,
                 std::function<void(const double)> _callback)
        : groupIndex(_groupIndex), displayString(_displayString), value(_choiceIndex), choices(_choices),
          callback(_callback), valueType(ValueType::Custom) {}

Setting::Setting(const uint8_t _group,
                 const std::string &_displayString,
                 std::function<void(const double)> _callback, const bool isAction)
        : groupIndex(_group), displayString(_displayString), callback(_callback),
          valueType(ValueType::Action) {}

void Setting::operator++(int) {
    switch (valueType) {
        case ValueType::Boolean:
            value = !value;
            break;
        case ValueType::Integer:
            value = constrain(++value, minValue, maxValue);
            break;
        case ValueType::Custom:
            value = constrain(++value, 0, choices.size() - 1);
            break;
        case ValueType::Float:
            value = constrain(value + 0.01, minValue, maxValue);
            callback(value);
            break;
        case ValueType::Action:
            value = !value;
            callback(value);
            break;
        default:
            break;
    }
}

void Setting::operator--(int) {
    switch (valueType) {
        case ValueType::Boolean:
            value = !value;
            break;
        case ValueType::Integer:
            value = constrain(--value, minValue, maxValue);
            break;
        case ValueType::Custom:
            value = constrain(--value, 0, choices.size() - 1);
            break;
        case ValueType::Float:
            value = constrain(value - 0.01, minValue, maxValue);
            callback(value);
            break;
        case ValueType::Action:
            value = !value;
            callback(value);
            break;
        default:
            break;
    }
}

const std::string Setting::getValueString() const {
    switch (valueType) {
        case ValueType::Custom:
            return (choices.size() > 0) ? choices[constrain(value, 0, choices.size() - 1)] : "???";
        case ValueType::Boolean:
            return value ? "true" : "false";
        case ValueType::Float:
            char floatBuffer[16];
            snprintf(floatBuffer, sizeof(floatBuffer), "%2.2f", value);
            return floatBuffer;
        case ValueType::Integer:
            char intBuffer[16];
            snprintf(intBuffer, sizeof(floatBuffer), "%f", value);
            return intBuffer;
        case ValueType::Action:
            return "EXEC";
    }

    return "???";
}

void Setting::setValue(const double newValue) {
    value = newValue;
    callback(value);
}

void Setting::exec() {
    value = !value;
    callback(value);
}