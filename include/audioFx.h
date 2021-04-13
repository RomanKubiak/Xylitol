//
// Created by atom on 22.03.2021.
//

#ifndef XYLITOL_AUDIOFX_H
#define XYLITOL_AUDIOFX_H

#include "config.h"
#include <Audio.h>
#include <vector>
#include "utils.h"

namespace Xylitol {
    class Manager;

    struct AudioEnvParam {
        double dly;
        double att;
        double hld;
        double dcy;
        double sus;
        double rel;
    };

    struct AudioParams {
        bool polyMode = true;

        AudioEnvParam envAmpFlanger = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
        int flangeIdx = 3 * FLANGE_DELAY_LENGTH / 4;
        int flangeDepth = FLANGE_DELAY_LENGTH / 8;
        double flangeFreq = 0.0625;

        AudioEnvParam envAmpFilter = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
        AudioEnvParam envModFilter = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
        double filterFreq = 440;
        double filterReso = 0.1;
        double filterFeedback = 0.0;
        double filterFeedbackMod = 0.0;

        AudioEnvParam envAmpMultiply = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
        uint8_t modShape = 0;
        double modFreq = 110;

        AudioEnvParam envAmpDelay = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
        double delayTap0 = 410;
        double delayTap1 = 520;
        double delayTap2 = 630;

        AudioEnvParam envAmpBitcrush= {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
        double bitcrushFreq = 44100 / 4;
        int bitcrushSamples = 12;

        AudioEnvParam envAmpGranular= {0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
    };

    enum class AudioPath : uint8_t {
        Flanger,
        Filter,
        Multiply,
        Delay,
        Bitcrush,
        Granular,
        Direct,
        AllPaths
    };

    class AudioFx {
    public:
        AudioFx(Manager &_manager);

        void begin();

        void setPath(const AudioPath path, const double amp);

        void update();

        void setupBasicPaths();

        AudioParams &getAudioParams() { return audioParams; }
    private:
        std::vector<double> paths = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        AudioParams audioParams;
        Manager &manager;
    };

    static const inline void appylEnvParams(const AudioEnvParam &p, AudioEffectEnvelope &env) {
        env.delay(p.dly);
        env.attack(p.att);
        env.hold(p.hld);
        env.decay(p.dcy);
        env.sustain(p.sus);
        env.release(p.rel);
    }
};

#endif //XYLITOL_AUDIOFX_H
