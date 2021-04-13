#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            lineInput;      //xy=56.5,403
AudioPlaySdWav           playSdWav1;     //xy=69.5,477.00000190734863
AudioMixer4              inputMixer;         //xy=266,417.00000190734863
AudioAnalyzeRMS          rms1;           //xy=508,229.0000114440918
AudioAmplifier           ampInDirect;           //xy=537.3335494995117,561.6667766571045
AudioAmplifier           ampInFilter;    //xy=539.5,408.0000114440918
AudioAmplifier           ampInDelay;     //xy=542.5,468.0000114440918
AudioAmplifier           ampInFlanger;   //xy=546.5,378.0000114440918
AudioAmplifier           ampInMultiply;  //xy=548.5,438.0000114440918
AudioAmplifier           ampInGranular;  //xy=548.5,529.0000114440918
AudioAmplifier           ampInBitcrusher; //xy=554.5,497.0000114440918
AudioSynthWaveformDc     dc1;            //xy=789.6667098999023,380.6666679382324
AudioEffectEnvelope      envModFilter;      //xy=799.6667861938477,345.6666679382324
AudioSynthWaveform       oscModFilter;      //xy=813.6667098999023,448.66666984558105
AudioSynthWaveform       oscModMultiply;  //xy=814.5005111694336,570.0001811981201
AudioMixer4              mixInDelay;         //xy=824.8889427185059,668.222225189209
AudioEffectDelay         fxDelay;        //xy=838.5003356933594,883.0003356933594
AudioAmplifier           ampFbkDelay2;           //xy=861.8890380859375,807.2223491668701
AudioAmplifier           ampFbkDelay1;           //xy=863.8891868591309,777.2224397659302
AudioAmplifier           ampFbkDelay0;           //xy=864.8890647888184,745.2224397659302
AudioFilterStateVariable fxFilter;       //xy=895.5002059936523,244.0000762939453
AudioEffectGranular      granular1;      //xy=922.5002708435059,1230.0002422332764
AudioEffectMultiply      fxMultiply;     //xy=926.5003623962402,528.0001811981201
AudioEffectFlange        fxFlanger;      //xy=932.5002059936523,88.00005054473877
AudioEffectBitcrusher    bitcrusher1;    //xy=930.5003280639648,1185.0002727508545
AudioAmplifier           ampFilterFeedback; //xy=935.5002059936523,150.0001106262207
AudioMixer4              mixDelayTaps;        //xy=999.5157089233398,855.5156211853027
AudioMixer4              mixFilterMod;         //xy=1005.666877746582,337.66668701171875
AudioMixer4              mixFilter;         //xy=1034.6666564941406,247.66666412353516
AudioAmplifier           ampFilterFeedbackMod;           //xy=1050.6668167114258,413.66670989990234
AudioEffectEnvelope      envAmpFilter; //xy=1326.515682220459,367.5156605243683
AudioEffectEnvelope      envAmpDelay; //xy=1330.5156173706055,427.5156841278076
AudioEffectEnvelope      envAmpFlanger;      //xy=1334.5156784057617,335.51563787460327
AudioEffectEnvelope      envAmpMultiply; //xy=1334.5158042907715,397.51562213897705
AudioEffectEnvelope      envAmpBitcrush; //xy=1339.5156784057617,456.5156536102295
AudioEffectEnvelope      envAmpGranular; //xy=1340.5156784057617,487.51563835144043
AudioMixer4              mixer7;         //xy=1644.4999961853027,498.0002498626709
AudioMixer4              mixer2;         //xy=1647.4999961853027,429.00001335144043
AudioMixer4              mixer8;         //xy=1827.5001182556152,545.0002269744873
AudioOutputI2S           lineOutput;     //xy=2053.5001487731934,517.0002107620239
AudioConnection          patchCord1(lineInput, 0, inputMixer, 0);
AudioConnection          patchCord2(lineInput, 1, inputMixer, 1);
AudioConnection          patchCord3(playSdWav1, 0, inputMixer, 2);
AudioConnection          patchCord4(playSdWav1, 1, inputMixer, 3);
AudioConnection          patchCord5(inputMixer, ampInFlanger);
AudioConnection          patchCord6(inputMixer, ampInFilter);
AudioConnection          patchCord7(inputMixer, ampInMultiply);
AudioConnection          patchCord8(inputMixer, ampInDelay);
AudioConnection          patchCord9(inputMixer, ampInBitcrusher);
AudioConnection          patchCord10(inputMixer, ampInGranular);
AudioConnection          patchCord11(inputMixer, rms1);
AudioConnection          patchCord12(inputMixer, ampInDirect);
AudioConnection          patchCord13(ampInDirect, 0, mixer8, 3);
AudioConnection          patchCord14(ampInFilter, 0, fxFilter, 0);
AudioConnection          patchCord15(ampInDelay, 0, mixInDelay, 0);
AudioConnection          patchCord16(ampInFlanger, fxFlanger);
AudioConnection          patchCord17(ampInMultiply, 0, fxMultiply, 0);
AudioConnection          patchCord18(ampInGranular, granular1);
AudioConnection          patchCord19(ampInBitcrusher, bitcrusher1);
AudioConnection          patchCord20(dc1, envModFilter);
AudioConnection          patchCord21(envModFilter, 0, mixFilterMod, 0);
AudioConnection          patchCord22(oscModFilter, 0, mixFilterMod, 2);
AudioConnection          patchCord23(oscModMultiply, 0, fxMultiply, 1);
AudioConnection          patchCord24(mixInDelay, fxDelay);
AudioConnection          patchCord25(fxDelay, 0, ampFbkDelay0, 0);
AudioConnection          patchCord26(fxDelay, 0, mixDelayTaps, 0);
AudioConnection          patchCord27(fxDelay, 1, ampFbkDelay1, 0);
AudioConnection          patchCord28(fxDelay, 1, mixDelayTaps, 1);
AudioConnection          patchCord29(fxDelay, 2, ampFbkDelay2, 0);
AudioConnection          patchCord30(fxDelay, 2, mixDelayTaps, 2);
AudioConnection          patchCord31(ampFbkDelay2, 0, mixInDelay, 3);
AudioConnection          patchCord32(ampFbkDelay1, 0, mixInDelay, 2);
AudioConnection          patchCord33(ampFbkDelay0, 0, mixInDelay, 1);
AudioConnection          patchCord34(fxFilter, 0, mixFilter, 0);
AudioConnection          patchCord35(fxFilter, 1, mixFilter, 1);
AudioConnection          patchCord36(fxFilter, 2, mixFilter, 2);
AudioConnection          patchCord37(granular1, envAmpGranular);
AudioConnection          patchCord38(fxMultiply, envAmpMultiply);
AudioConnection          patchCord39(fxFlanger, envAmpFlanger);
AudioConnection          patchCord40(bitcrusher1, envAmpBitcrush);
AudioConnection          patchCord41(ampFilterFeedback, 0, fxFilter, 0);
AudioConnection          patchCord42(mixDelayTaps, envAmpDelay);
AudioConnection          patchCord43(mixFilterMod, 0, fxFilter, 1);
AudioConnection          patchCord44(mixFilter, ampFilterFeedback);
AudioConnection          patchCord45(mixFilter, ampFilterFeedbackMod);
AudioConnection          patchCord46(mixFilter, envAmpFilter);
AudioConnection          patchCord47(ampFilterFeedbackMod, 0, mixFilterMod, 1);
AudioConnection          patchCord48(envAmpFilter, 0, mixer2, 1);
AudioConnection          patchCord49(envAmpDelay, 0, mixer2, 3);
AudioConnection          patchCord50(envAmpFlanger, 0, mixer2, 0);
AudioConnection          patchCord51(envAmpMultiply, 0, mixer2, 2);
AudioConnection          patchCord52(envAmpBitcrush, 0, mixer7, 0);
AudioConnection          patchCord53(envAmpGranular, 0, mixer7, 1);
AudioConnection          patchCord54(mixer7, 0, mixer8, 2);
AudioConnection          patchCord55(mixer2, 0, mixer8, 0);
AudioConnection          patchCord56(mixer8, 0, lineOutput, 0);
AudioConnection          patchCord57(mixer8, 0, lineOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1388.4999923706055,103.000009059906
// GUItool: end automatically generated code

#include "config.h"
#include "manager.h"
#include "menu.h"
#include "matrixSequencer.h"
#include "ClickButton.h"

using namespace Xylitol;
Manager manager;

void setup() {
	Serial.begin(115200);
    AudioMemory(250);
	sgtl5000_1.enable();  // Enable the audio shield
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.volume(0.7);

    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
        // stop here, but print a message repetitively
        while (1) {
        Serial.println("Unable to access the SD card");
        delay(500);
        }
    } else {
        Serial.println("SD card initialized");
    }

    delay(1500);
    manager.begin();
}

elapsedMillis fps;
bool led = false;
void loop()
{
    if (!playSdWav1.isPlaying()) {
        playSdWav1.play("orig.wav");
        Serial.println("playin wav");
    }



	while (usbMIDI.read())
    {
	    if (usbMIDI.getType() == usb_midi_class::NoteOn)
        {
        }

        if (usbMIDI.getType() == usb_midi_class::NoteOff)
        {
        }

        if (manager.matrixSequencer->isSlave()) {
            if (usbMIDI.getType() == usb_midi_class::Clock) { manager.matrixSequencer->midiClock(); }
            if (usbMIDI.getType() == usb_midi_class::Start) { manager.matrixSequencer->midiClockStart(); }
            if (usbMIDI.getType() == usb_midi_class::Stop) { manager.matrixSequencer->midiClockStop(); }
            if (usbMIDI.getType() == usb_midi_class::Continue) { manager.matrixSequencer->midiClockContinue(); }
        }
    }

	manager.update();
}

