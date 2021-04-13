#pragma once

#include "config.h"
#include <string>
#include <ADC.h>
#include <vector>

namespace Xylitol {

    struct PotInput {
        const uint8_t pin;
        ResponsiveAnalogRead resp;
        std::function<void(PotInput &)> callback;
    };

    enum PotsOnBoard {
        pot1, pot2, pot3, pot4,
        pot5, pot6, pot7, pot8
    };
    class Manager;
    class AnalInput {
    public:
        AnalInput(Manager &_manager);

        ~AnalInput() {}

        void begin();

        void update();

        void potChanged(PotInput &pot);

        void setCallback(const Xylitol::PotsOnBoard potOnBoard, std::function <void(PotInput)> cbk);

    private:
        Manager &manager;
        ADC adc;
        std::vector<PotInput> pots;
    };
};