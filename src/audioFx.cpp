//
// Created by atom on 22.03.2021.
//
#include "audioFx.h"
#include "manager.h"
extern AudioMixer4 inputMixer;
extern AudioMixer4 mixer2;
extern AudioMixer4 mixer7;
extern AudioMixer4 mixer8;

extern AudioAmplifier ampInDirect;

short flangerMemory[FLANGE_DELAY_LENGTH];
extern AudioEffectEnvelope envAmpFlanger;
extern AudioEffectFlange fxFlanger;
extern AudioAmplifier ampInFlanger;

extern AudioSynthWaveform oscModMultiply;
extern AudioAmplifier ampInMultiply;
extern AudioEffectEnvelope envAmpMultiply;

int16_t granularMemory[GRANULAR_MEMORY_SIZE];
extern AudioAmplifier ampInGranular;
extern AudioEffectGranular granular1;
extern AudioEffectEnvelope envAmpGranular;

extern AudioEffectEnvelope      envAmpBitcrush;
extern AudioAmplifier ampInBitcrusher;
extern AudioEffectBitcrusher bitcrusher1;

extern AudioEffectEnvelope      envAmpFilter;
extern AudioFilterStateVariable fxFilter;
extern AudioEffectEnvelope envModFilter;
extern AudioAmplifier ampInFilter;

extern AudioAmplifier ampInDelay;
extern AudioEffectDelay  fxDelay;
extern AudioMixer4  mixDelayTaps;
extern AudioAmplifier ampFbkDelay0;
extern AudioAmplifier ampFbkDelay1;
extern AudioAmplifier ampFbkDelay2;
extern AudioEffectEnvelope envAmpDelay;


using namespace Xylitol;

AudioFx::AudioFx(Manager &_manager) : manager(_manager)
{
}

void AudioFx::setupBasicPaths()
{
    inputMixer.gain(0, 1.0);
    inputMixer.gain(1, 1.0);

    inputMixer.gain(2, 1.0);
    inputMixer.gain(3, 1.0);

    mixer2.gain(0, 1.0);
    mixer2.gain(1, 0.0);
    mixer2.gain(2, 1.0);
    mixer2.gain(3, 1.0);

    mixer7.gain(0, 1.0);
    mixer7.gain(1, 1.0);
    mixer7.gain(2, 1.0);
    mixer7.gain(3, 1.0);

    mixer8.gain(0, 1.0);
    mixer8.gain(1, 1.0);
    mixer8.gain(2, 1.0);
    mixer8.gain(3, 1.0);
}

void AudioFx::begin()
{
    setupBasicPaths();

    {
        appylEnvParams(audioParams.envAmpFlanger, envAmpFlanger);
        appylEnvParams(audioParams.envAmpFilter, envAmpFilter);
        appylEnvParams(audioParams.envAmpMultiply, envAmpMultiply);
        appylEnvParams(audioParams.envAmpDelay, envAmpDelay);
        appylEnvParams(audioParams.envAmpBitcrush, envAmpBitcrush);
        appylEnvParams(audioParams.envAmpGranular, envAmpGranular);
    }

    {
        fxFlanger.begin(flangerMemory,
                        FLANGE_DELAY_LENGTH,
                        audioParams.flangeIdx,
                        audioParams.flangeDepth,
                        audioParams.flangeFreq);
        fxFlanger.voices(audioParams.flangeIdx, audioParams.flangeDepth, audioParams.flangeFreq);
    }

    {
        fxDelay.delay(0, audioParams.delayTap0);
        fxDelay.delay(1, audioParams.delayTap1);
        fxDelay.delay(2, audioParams.delayTap2);

        ampFbkDelay0.gain(0);
        ampFbkDelay1.gain(0);
        ampFbkDelay2.gain(0);

        mixDelayTaps.gain(0, 1.0);
        mixDelayTaps.gain(1, 1.0);
        mixDelayTaps.gain(2, 1.0);
        mixDelayTaps.gain(3, 0.0);
    }

    oscModMultiply.begin(audioParams.modShape);
    oscModMultiply.frequency(audioParams.modFreq);
    oscModMultiply.amplitude(1.0);

    bitcrusher1.sampleRate(audioParams.bitcrushFreq);
    bitcrusher1.bits(audioParams.bitcrushSamples);

    fxFilter.frequency(audioParams.filterFreq);
    fxFilter.resonance(audioParams.filterReso);

    granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);

    setPath(Xylitol::AudioPath::Flanger, 0.0);
    setPath(Xylitol::AudioPath::Filter, 0.0);
    setPath(Xylitol::AudioPath::Multiply, 0.0);
    setPath(Xylitol::AudioPath::Delay, 0.0);
    setPath(Xylitol::AudioPath::Bitcrush, 0.0);
    setPath(Xylitol::AudioPath::Granular, 0.0);
    setPath(Xylitol::AudioPath::Direct, 1.0);
}

static const std::string pathToName(const AudioPath &path) {
    switch (path) {
        case AudioPath::Flanger:
            return ("Flanger");
        case AudioPath::Filter:
            return ("Filter");
        case AudioPath::Multiply:
            return ("Multiply");
        case AudioPath::Delay:
            return ("Delay");
        case AudioPath::Bitcrush:
            return ("Bitcrush");
        case AudioPath::Granular:
            return ("Granular");
        case AudioPath::Direct:
            return ("Direct");
        default:
            return ("Unknown");
    }
}

void AudioFx::setPath(const AudioPath path, const double amp) {
    if (audioParams.polyMode == false) {
        ampInFlanger.gain(0.0);
        ampInFilter.gain(0.0);
        ampInMultiply.gain(0.0);
        ampInDelay.gain(0.0);
        ampInBitcrusher.gain(0.0);
        ampInGranular.gain(0.0);
        ampInDirect.gain(0.0);
    }

    AudioNoInterrupts();

    switch (path) {
        case AudioPath::Flanger:
            if (amp > 0)
                envAmpFlanger.noteOn();
            else
                envAmpFlanger.noteOff();
            ampInFlanger.gain(amp);
            break;
        case AudioPath::Filter:
            if (amp > 0)
                envAmpFilter.noteOn();
            else
                envAmpFilter.noteOff();
            ampInFilter.gain(amp);
            break;
        case AudioPath::Multiply:
            if (amp > 0)
                envAmpMultiply.noteOn();
            else
                envAmpMultiply.noteOff();
            ampInMultiply.gain(amp);
            break;
        case AudioPath::Delay:
            if (amp > 0)
                envAmpDelay.noteOn();
            else
                envAmpDelay.noteOff();
            ampInDelay.gain(amp);
            break;
        case AudioPath::Bitcrush:
            if (amp > 0)
                envAmpBitcrush.noteOn();
            else
                envAmpBitcrush.noteOff();
            ampInBitcrusher.gain(amp);
            break;
        case AudioPath::Granular:
            if (amp > 0)
                envAmpGranular.noteOn();
            else
                envAmpGranular.noteOff();
            ampInGranular.gain(amp);
            break;
        case AudioPath::Direct:
            ampInDirect.gain(amp);
            break;
        default:
            break;
    }

    AudioInterrupts();

    paths[static_cast<int>(path)] = amp;
}

void AudioFx::update()
{
    envAmpFlanger.update();
    envAmpFilter.update();
    envModFilter.update();
    envAmpBitcrush.update();
    envAmpGranular.update();
    envAmpDelay.update();
    envAmpMultiply.update();
}
