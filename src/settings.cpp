//
// Created by atom on 07.03.2021.
//

#include "settings.h"
#include <string>
#include "manager.h"
#include "matrixSequencer.h"
namespace Xylitol {

    Settings::Settings(Manager &_manager) : manager(_manager),
                                            settings{
                                                    {groupSGTL5000, "Volume",           0.0,        0.0, 1.0, [](
                                                            const double v) {
                                                        sgtl5000_1.volume(v);
                                                    }},
                                                    {groupSGTL5000, "Input select",     {"Line in", "Microphone"}},
                                                    {groupSGTL5000, "MIC Gain",         0L,         0L,  63L},
                                                    {groupSGTL5000, "Mute headphones",  false},
                                                    {groupSGTL5000, "Mute LineOut",     false},
                                                    {groupSGTL5000, "LIN Level Left",   ppVoltsIn,  5},
                                                    {groupSGTL5000, "LIN Level Right",  ppVoltsIn,  5},
                                                    {groupSGTL5000, "LOUT Level Left",  ppVoltsOut, 16},
                                                    {groupSGTL5000, "LOUT Level Right", ppVoltsOut, 16},
                                                    {groupSGTL5000, "ADC HP Freeze",    false},
                                                    {groupSGTL5000, "ADC HP Enable",    false},
                                                    {groupRoot, "Gen rand patt",    [&](const double v) {
                                                        getManager().matrixSequencer->reset();
                                                        getManager().matrixSequencer->generateRandomPattern();
                                                        getManager().matrixSequencer->renderTracks();
                                                        }, true }}
                                                    {
    }

    Setting &Settings::getByIndex(const uint16_t index) {
        if (index >= 0 && index < settings.size()) {
            return settings[index];
        } else {
            return settings[0];
        }
    }
};