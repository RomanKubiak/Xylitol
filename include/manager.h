//
// Created by atom on 03.04.2021.
//

#ifndef XYLITOL_MANAGER_H
#define XYLITOL_MANAGER_H

#include "settings.h"
#include "analIn.h"
#include "buttons.h"
#include <TimerOne.h>
#include <memory>

namespace Xylitol {
    static constexpr auto settingsFilename = "settings.txt";

    class Menu;
    class AudioFx;
    class SerialLeds;
    class MatrixSequencer;

    class Manager {
    public:
        Manager();
        ~Manager();

        void saveSettingsNow();
        void readSettings();
        void begin();
        void update();

        std::unique_ptr<Settings> settings;
        std::unique_ptr<Menu> menu;
        std::unique_ptr<AudioFx> audioFx;
        std::unique_ptr<SerialLeds> serialLeds;
        AnalInput analogInputs;
        Buttons buttons;
        std::unique_ptr<MatrixSequencer> matrixSequencer;

    private:
        bool editMode;
        elapsedMillis rmsFPS, matrixFPS;
    };

}
#endif //XYLITOL_MANAGER_H
