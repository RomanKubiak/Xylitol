#pragma once

#include <vector>
#include "config.h"
#include "../lib/ClickButton/ClickButton.h"

namespace Xylitol {
    enum class LowLevelHandlerClass {
        click,
        bounce
    };

    class ButtonInput {
    public:
        ButtonInput(const Xylitol::LowLevelHandlerClass _lowLevelHandler,
                    int pin,
                    std::string _name,
                    const bool activeType = LOW,
                    const bool interalPullup = true)
                : lowLevelHandler(_lowLevelHandler), name(_name) {
            if (lowLevelHandler == LowLevelHandlerClass::click)
                clickButton = new ClickButton(pin, activeType, interalPullup);
            else {
                bounce2 = new Bounce();
                bounce2->attach(pin, INPUT_PULLUP);
            }
        }

        ~ButtonInput() {}
        bool clickDetected()
        {
            if (lowLevelHandler == LowLevelHandlerClass::click) {
                return clickButton->changed;
            }

            if (lowLevelHandler == LowLevelHandlerClass::bounce) {
                return bounce2->fell();
            }

            return false;
        }

        bool wasHeld() {
            if (lowLevelHandler == LowLevelHandlerClass::click) {
                return clickButton->clicks == -1;
            }

            if (lowLevelHandler == LowLevelHandlerClass::bounce) {
                return false;
            }

            return false;
        }
        LowLevelHandlerClass lowLevelHandler;
        std::string name;
        ClickButton *clickButton;
        Bounce *bounce2;
        std::function<void(ButtonInput &)> callback;
    };

    enum ButtonsOnBoard {
        Right,
        Left,
        Up,
        Down,
        SequencerButton,
        EncoderButton,
        NumButtons
    };

    class Manager;

    class Buttons {
    public:
        Buttons(Manager &_manager);

        void begin();

        void update();

        void buttonChanged(Xylitol::ButtonInput &button);

        void setCallback(const ButtonsOnBoard btn, std::function<void(ButtonInput &)> cbk);

        std::vector<Xylitol::ButtonInput> buttons = {
                {Xylitol::LowLevelHandlerClass::bounce, BUTTON0,     "Right"},
                {Xylitol::LowLevelHandlerClass::bounce, BUTTON1,     "Left"},
                {Xylitol::LowLevelHandlerClass::bounce, BUTTON2,     "Down"},
                {Xylitol::LowLevelHandlerClass::bounce, BUTTON3,     "Up"},
                {Xylitol::LowLevelHandlerClass::bounce,  BUTTON4,     "Mode"},
                {Xylitol::LowLevelHandlerClass::click,  ENCODER_BTN, "EncoderButton"},
        };

    private:
        Manager &manager;
    };

};