#pragma once

#include "config.h"
#include "settings.h"
#include <map>

namespace Xylitol {
    class Manager;
    class Menu {
    public:
        Menu(Manager &_manager);
        void begin();
        void update();
        void encoderValueChanged(const int32_t &encoderValue);
        void encoderButtonClicked();
        void setLedRingValue(const uint8_t &value, bool bottomLedOn);

    private:
        int32_t currentItemSelected = -1;
        int32_t currentItemChanged = -1;
        bool changingValue = false;
        int32_t oldPos = 0;
        char stringBuf[16];
        Manager &manager;
    };
};