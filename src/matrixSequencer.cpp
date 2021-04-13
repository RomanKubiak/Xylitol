#include "matrixSequencer.h"
#include "manager.h"
#include "buttons.h"
#include "menu.h"
#include <Entropy.h>

#define RNG_CR			(*(volatile uint32_t *)0x40029000) // RNGA Control Register
#define RNG_SR			(*(volatile uint32_t *)0x40029004) // RNGA Status Register
#define RNG_ER			(*(volatile uint32_t *)0x40029008) // RNGA Entropy Register
#define RNG_OR          (*(volatile uint32_t *)0x4002900C) // RNGA Output Register
#define RNG_CR_GO_MASK                           0x1u
#define RNG_CR_HA_MASK                           0x2u
#define RNG_CR_INTM_MASK                         0x4u
#define RNG_CR_CLRI_MASK                         0x8u
#define RNG_CR_SLP_MASK                          0x10u
#define RNG_SR_OREG_LVL_MASK                     0xFF00u
#define RNG_SR_OREG_LVL_SHIFT                    8
#define RNG_SR_OREG_LVL(x)                       (((uint32_t)(((uint32_t)(x))<<RNG_SR_OREG_LVL_SHIFT))&RNG_SR_OREG_LVL_MASK)
#define SIM_SCGC6_RNGA    ((uint32_t)0x00000200)

#define p(x) Serial.print(x)
#define pln(x) Serial.println(x)

uint32_t trng(){
    RNG_CR |= RNG_CR_GO_MASK;
    while((RNG_SR & RNG_SR_OREG_LVL(0xF)) == 0); // wait
    return RNG_OR;
}

extern Xylitol::Manager manager;

void midiClockFunction()
{
    manager.matrixSequencer->timerOneCallback();
}

using namespace Xylitol;

MatrixSequencer::MatrixSequencer(Manager &_manager)
        : currentPosition(0), clockCounter(0), manager(_manager) {
}

void MatrixSequencer::reset() {
    lc.clearDisplay(0);
    lc.clearDisplay(1);
    for (auto &track: tracks) {
        for (auto &step : track.steps) {
            step.lengthIn16ths = 1;
            step.isActive = false;
            step.ppqOffset = 0;
            step.audioParams = nullptr;
        }
    }
}

void MatrixSequencer::begin() {
    Entropy.Initialize();
    randomSeed(Entropy.random());

    lc.shutdown(0, false);
    lc.shutdown(1, false);
    /* Set the brightness to a medium values */
    lc.setIntensity(0, 8);
    lc.setIntensity(1, 8);
    lc.clearDisplay(0);
    lc.clearDisplay(1);

    manager.buttons.setCallback(Xylitol::ButtonsOnBoard::Up, [&](Xylitol::ButtonInput &s) {
        if (!s.clickDetected()) return;
        cursor.previousY = cursor.y;
        cursor.y = constrain(++cursor.y, 0, 7);
    });

    manager.buttons.setCallback(Xylitol::ButtonsOnBoard::Down, [&](Xylitol::ButtonInput &s) {
        if (!s.clickDetected()) return;
        cursor.previousY = cursor.y;
        cursor.y = constrain(--cursor.y, 0, 7);
    });
    manager.buttons.setCallback(Xylitol::ButtonsOnBoard::Left, [&](Xylitol::ButtonInput &s) {
        if (!s.clickDetected()) return;
        cursor.previousX = cursor.x;
        cursor.x = constrain(--cursor.x, 0, 15);
    });

    manager.buttons.setCallback(Xylitol::ButtonsOnBoard::Right, [&](Xylitol::ButtonInput &s) {
        if (!s.clickDetected()) return;
        cursor.previousX = cursor.x;
        cursor.x = constrain(++cursor.x, 0, 15);
    });

    manager.buttons.setCallback(Xylitol::ButtonsOnBoard::SequencerButton, [&](Xylitol::ButtonInput &s) {
        if (!s.clickDetected()) return;

        toggleEditMode();
    });

    for (uint8_t y = 0; y < tracks.size(); y++) {
        for (uint8_t x = 0; x < SEQ_MAX_STEPS_PER_TRACK; x++) {
            tracks[y].steps.push_back({nullptr, 1, 0, false});
        }
    }

    reset();
    generateRandomPattern();
    renderTracks();
    Timer1.initialize(calculateIntervalMicroSecs(120));
    Timer1.attachInterrupt(midiClockFunction);
    setSlaveToMIDI(false, 110);
}

void MatrixSequencer::update() {
    if (cursorFPS > 70) {
        cursorFPS = 0;
        renderCursor();
    }
}

void MatrixSequencer::generateRandomPattern() {
    for (auto &track: tracks) {
        const uint8_t step = random(16);
        const bool isActive = random(2);
        const uint8_t len = constrain(random(16-step), (const uint8_t)0, (const uint8_t)5);
        p("step="); p(step); p(" isActive="); p(isActive);
        p(" len="); pln(len);

        track.steps[step].isActive = isActive;
        for (uint8_t i = step; i<len; i++) {
            track.steps[i].isActive = true;
        }
    }
}

void MatrixSequencer::updatePositionByLed() {
    for (int y = 0; y < 8; y++) {
        if (tracks[y].steps[currentPosition].isActive)
            setLed(currentPosition, y, LOW);
        else
            setLed(currentPosition, y, HIGH);
    }

    for (int y = 0; y < 8; y++) {
        if (tracks[y].steps[currentPosition - 1].isActive)
            setLed(currentPosition - 1, y, HIGH);
        else
            setLed(currentPosition - 1, y, LOW);
    }

    if (currentPosition == 0) {
        for (int i = 0; i < 8; i++)
            setLed(15, i, LOW);
    }
}

void MatrixSequencer::renderCursor() {
    if (!editMode)
        return;

    setLed(cursor.x, cursor.y, cursor.state);

    if (cursor.x != cursor.previousX)
        setLed(cursor.previousX, cursor.y, LOW);

    if (cursor.y != cursor.previousY)
        setLed(cursor.x, cursor.previousY, LOW);

    cursor.state = !cursor.state;
}

void MatrixSequencer::toggleEditMode() {
    editMode = !editMode;
    if (!editMode) setLed(cursor.x, cursor.y, LOW);
}

void MatrixSequencer::renderTracks() {
    for (uint8_t y = 0; y < tracks.size(); y++) {
        for (uint8_t x = 0; x < tracks[y].steps.size(); x++) {
            for (uint8_t len = 0; len < tracks[y].steps[y].lengthIn16ths; len++) {
                setLed(x+len, y, tracks[y].steps[x].isActive);
            }
        }
    }
}

void MatrixSequencer::initTracks() {
    for (auto &track: tracks) {
        for (auto &step: track.steps) {
            if (manager.audioFx) {
                step.audioParams = &manager.audioFx->getAudioParams();
                step.lengthIn16ths = 1;
                step.ppqOffset = 0;
            }
        }
    }
}

void MatrixSequencer::midiClock() {
    clockCounter++;
    if (clockCounter == (CLOCKS_PER_BEAT / SIXTEENTH_NOTE)) {
        if (currentPosition == 16) {
            currentPosition = 0;
        }

        if (currentPosition != previousPosition) {
            previousPosition = currentPosition;
            updatePositionByLed();
            // updatePositionByColumn();
        }
        currentPosition++;
        clockCounter = 0;
    }
}

void MatrixSequencer::midiClockStart() {
    clockCounter = 0;
    previousPosition = -1;
    currentPosition = 0;
}

void MatrixSequencer::midiClockStop() {
    clockCounter = 0;
}

void MatrixSequencer::midiClockContinue() {

}

void MatrixSequencer::setBPM(const double _bpm)
{
    bpm = _bpm;
    calculateAndSetTimerForBPM(bpm);
}

void MatrixSequencer::calculateAndSetTimerForBPM(const double bpm) {
    Timer1.setPeriod(calculateIntervalMicroSecs(bpm));
}

void MatrixSequencer::timerOneCallback()
{
    midiClock();
}

void MatrixSequencer::setSlaveToMIDI(const bool isSlave, const double _bpm)
{
    isSlaveToMIDI = isSlave;
    if (!isSlave) {
        setBPM(_bpm);
    } else {
        Timer1.stop();
    }
}