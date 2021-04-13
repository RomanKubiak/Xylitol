//
// Created by atom on 03.04.2021.
//
#include <ArduinoJson.h>
#include "manager.h"
#include "settings.h"
#include "audioFx.h"
#include "menu.h"
#include "buttons.h"
#include "serialLeds.hpp"
#include "matrixSequencer.h"
#include <SD.h>

extern AudioAnalyzeRMS rms1;
using namespace Xylitol;

Manager::Manager() : analogInputs(*this), buttons(*this) {
    Serial.println("Manager::ctor starts");

    settings = std::make_unique<Settings>(*this);
    menu = std::make_unique<Menu> (*this);
    audioFx = std::make_unique<AudioFx> (*this);
    serialLeds = std::make_unique<SerialLeds> (*this);
    matrixSequencer = std::make_unique<MatrixSequencer> (*this);
    Serial.println("Manager::ctor ends");
}

Manager::~Manager() {
}

void Manager::begin() {
    Serial.println("Manager::begin starts");
    analogInputs.begin();
    buttons.begin();

    if (serialLeds) serialLeds->begin();
    if (matrixSequencer) matrixSequencer->begin();
    if (audioFx) audioFx->begin();
    if (menu) menu->begin();

    buttons.setCallback(Xylitol::ButtonsOnBoard::EncoderButton, [&](ButtonInput &b) {
        Serial.print("manager::encoderButton changed detected: ");
        if (b.wasHeld()) {
            Serial.println("HELD");
            saveSettingsNow();
        } else if (b.clickDetected()) {
            Serial.println("CLICKED");
            if (menu) menu->encoderButtonClicked();
        }
    });


    Serial.println("Manager::begin ends");
}

void Manager::update() {
    analogInputs.update();
    buttons.update();

    if (audioFx) audioFx->update();
    if (menu) menu->update();

    if (rmsFPS > 24) {
        rmsFPS = 0;
        if (rms1.available()) {
            if (serialLeds) serialLeds->update(rms1.read());
        }
    }
    if (matrixSequencer) matrixSequencer->update();
}

void Manager::readSettings() {}

void Manager::saveSettingsNow() {
    AudioNoInterrupts();
    Serial.println("Manager::saveSettingsNow starts");
    Serial.print("size of audioParams: ");
    Serial.println(sizeof(audioFx->getAudioParams()));
    StaticJsonDocument<512> doc;
    File file = SD.open(settingsFilename, O_WRITE|O_CREAT|O_TRUNC);
    if (!file) {
        Serial.println(F("Failed to create file"));
        return;
    }

    for (int i=0; i<settings->getNumSettings(); i++) {
        doc[settings->getByIndex(i).getDisplayString()] = settings->getByIndex(i).getValue();
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println(F("Failed to write to file"));
    } else {
        Serial.println(F("Settings saved"));
        serializeJson(doc, Serial);
    }
    file.close();
    AudioInterrupts();
}