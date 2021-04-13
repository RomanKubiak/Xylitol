//
// Created by atom on 07.03.2021.
//

#pragma once

#include "setting.h"

extern AudioControlSGTL5000 sgtl5000_1;

namespace Xylitol {
    class Manager;
    static const auto groupRoot = 0;
    static const auto groupSGTL5000 = 1;

    class Settings {
    public:
        Settings(Manager &_manager);
        const std::string dump() const;
        Setting &getByIndex(const uint16_t index);
        const uint16_t getNumSettings() const { return settings.size(); }
        Manager &getManager() { return manager; }
    private:
        const std::vector<std::string> ppVoltsIn = {
                "0.24", "0.56", "0.48", "0.40", "0.34",
                "0.67", "0.79", "0.94", "1.11", "1.33",
                "1.58", "1.87", "2.22", "2.63", "3.12"
        };

        const std::vector<std::string> ppVoltsOut = {
                "1.16", "1.22", "1.29", "1.37", "1.44",
                "1.53", "1.62", "1.71", "1.80", "1.91",
                "2.02", "2.14", "2.26", "2.39", "2.53",
                "2.67", "2.83", "2.98", "3.16"
        };

        const std::vector<int> enhanceBassCutoffFreq{
                80, 100, 125, 150, 175, 200, 225
        };

        const std::vector<std::string> eqType{
                "flat", "parametric", "tone", "graphic"
        };

        const std::vector<std::string> eqBands{
                "115Hz", "330Hz", "990Hz", "3kHz", "9.9kHz"
        };

        Manager &manager;
        std::vector<Setting> settings;
    };
};