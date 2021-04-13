#pragma once

#include "config.h"
#include "audioFx.h"
#include <vector>
#include <bitset>

namespace Xylitol {
    class Manager;
    class MatrixSequencer {
    public:
        MatrixSequencer(Manager &_manager);
        void begin();
        void update();

        void renderCursor();
        void renderTracks();
        void toggleEditMode();

        void setBPM(const double bpm);
        void calculateAndSetTimerForBPM(const double bpm);
        void setStep(const uint8_t trackNumber, const uint8_t stepNumber, const uint8_t stepLength, const bool isActive);
        void initTracks();
        void reset();
        void updatePositionByLed();
        void updatePositionByColumn();
        void timerOneCallback();
        void setSlaveToMIDI(const bool isSlave, const double _bpm);
        void midiClock();
        void midiClockStart();
        void midiClockStop();
        void midiClockContinue();
        void generateRandomPattern();
        const bool isSlave() const { return isSlaveToMIDI; }

        const long calculateIntervalMicroSecs(int bpm) const
        {
            return 60L * 1000 * 1000  / bpm / CLOCKS_PER_BEAT;
        }

        inline void setLed(const uint8_t x, const uint8_t y, bool state)
        {
            lc.setLed(x > 7, 7 - y, (x > 7) ? 8 - (x - 7) : (7-x), state);
        }

    private:
        LedControl lc{MATRIX_DATA, MATRIX_CLK, MATRIX_LOAD, MATRIX_NUM};
        struct Step {
            Xylitol::AudioParams *audioParams = nullptr;
            uint8_t lengthIn16ths = 1;
            int8_t ppqOffset = 0;
            bool isActive = false;
        };

        struct Track {
            std::vector<Step> steps;
            uint32_t startPPQOffset = 0;
        };

        struct Cursor {
            int16_t x = 1;
            int16_t y = 1;
            int16_t previousX = 1;
            int16_t previousY = 1;
            int16_t length = 1;
            bool state = false;
        } cursor;

        // only 7 tracks on screen at a time
        std::vector<Track> tracks = { {}, {}, {}, {}, {}, {}, {}, {} };

        bool editMode = false;
        int currentPosition;
        int previousPosition;
        IntervalTimer teensyTimer;

        elapsedMillis cursorFPS, tracksFPS;
        uint32_t clockCounter;
        Manager &manager;
        bool isSlaveToMIDI = true;
        double bpm = 120;
        std::bitset<16> rowBits;
    };
};