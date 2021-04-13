#pragma once
#include <WS2812Serial.h>
#include "config.h"
namespace Xylitol {
    class Manager;
    class SerialLeds {
    public:
        SerialLeds(Manager &_manager);
        void begin();

        void update(const float peakValue);

        uint32_t Wheel(byte WheelPos);

        WS2812Serial *leds;

    private:
        int counter;
        Manager &manager;
    };
};