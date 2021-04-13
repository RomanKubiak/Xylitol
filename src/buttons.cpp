#include "buttons.h"

using namespace Xylitol;

Buttons::Buttons(Manager &_manager) : manager(_manager) {
    pinMode(BUTTON4, INPUT_PULLUP);
}

void Buttons::begin() {
}

void Buttons::update() {
    for (auto &button: buttons) {
        if (button.lowLevelHandler == Xylitol::LowLevelHandlerClass::click) {
            button.clickButton->Update();

            if (button.clickButton->clicks != 0)
                buttonChanged(button);
        }

        if (button.lowLevelHandler == Xylitol::LowLevelHandlerClass::bounce) {
            button.bounce2->update();

            if (button.bounce2->fell() || button.bounce2->rose())
                buttonChanged(button);
        }
    }
}

void Buttons::buttonChanged(ButtonInput &button) {
    Serial.print("button changed: ");
    Serial.println(button.name.c_str());
    if (button.callback)
        button.callback(button);
}

void Buttons::setCallback(const ButtonsOnBoard btn, std::function<void(ButtonInput &)> cbk) {
    buttons[btn].callback = cbk;
}