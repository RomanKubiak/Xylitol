#include "analIn.h"
#include "manager.h"

using namespace Xylitol;

AnalInput::AnalInput(Manager &_manager) : manager(_manager),
                                          pots{
                                                  {A10, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A11, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A12, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A13, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A17, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A16, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A15, ResponsiveAnalogRead(0, POT_SLEEP)},
                                                  {A14, ResponsiveAnalogRead(0, POT_SLEEP)}
                                          }

{
}

void AnalInput::begin() {
    for (auto &pot: pots) {
        Serial.print("pin "); Serial.print(pot.pin); Serial.println(" set to input");
        pinMode(pot.pin, INPUT);
        pot.resp.enableEdgeSnap();
    }
    adc.adc0->setAveraging(32);                                    // set number of averages
    adc.adc0->setResolution(10);                                   // set bits of resolution
    adc.adc0->setConversionSpeed(ADC_CONVERSION_SPEED::LOW_SPEED); // change the conversion speed
    adc.adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_LOW_SPEED);     // change the sampling speed
}

void AnalInput::update() {
    for (auto &pot: pots) {
        pot.resp.update(1024 - adc.analogRead(pot.pin));
        if (pot.resp.hasChanged()) {
            potChanged(pot);
        }
        delay(2);
    }
}

void AnalInput::potChanged(PotInput &pot) {
    if (pot.callback)
        pot.callback(pot);
}

void AnalInput::setCallback(const Xylitol::PotsOnBoard potOnBoard, std::function<void(PotInput)> cbk) {
    pots[potOnBoard].callback = cbk;
}