#include "menu.h"
#include <Encoder.h>
#include <rgb_lcd.h>
#include <map>
#include <manager.h>
#include "matrixSequencer.h"
#include "buttons.h"
rgb_lcd lcdOutput;
using namespace Xylitol;
unsigned int ledRingSeq[16] = {0x0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000,
                               0x2000, 0x4000};

Encoder encoderInput(ENCODER_A, ENCODER_B);

elapsedMillis sincePrint;

Menu::Menu(Manager &_manager) : manager(_manager)
{
}

void Menu::begin()
{
	pinMode(RING_SDI, OUTPUT);
	pinMode(RING_CLK, OUTPUT);
	pinMode(RING_LE, OUTPUT);
	pinMode(ENCODER_BTN, INPUT_PULLUP);

	lcdOutput.begin(16, 2);
	lcdOutput.setCursor(0, 0);
	lcdOutput.print("Xylitol ");
    AudioMemoryUsageMaxReset();

	currentItemSelected = 0;
}

void Menu::update()
{
	if (sincePrint > 128)
	{
		sincePrint = 0;
		lcdOutput.clear();
		lcdOutput.setCursor(0, 0);
		const auto &s = manager.settings->getByIndex(currentItemSelected);

		lcdOutput.print(s.getDisplayString().c_str());

		lcdOutput.setCursor(12, 1);
        if (s.getType() == Xylitol::ValueType::Action) {
            lcdOutput.setCursor(0, 1);
            lcdOutput.print("!");
        } else if (changingValue) {
			lcdOutput.setCursor(0, 1);
			lcdOutput.print(">");
		}

        lcdOutput.setCursor(1, 1);
        lcdOutput.print(s.getValueString().c_str());


		lcdOutput.setCursor(8, 1);
        snprintf(stringBuf, 16, "%2.0f:%hu:%hu", AudioProcessorUsage(), AudioMemoryUsage(), AudioMemoryUsageMax());
        lcdOutput.print(stringBuf);
	}

	const int32_t newPos = encoderInput.read();
	if ((newPos / 4) != oldPos)
	{
		encoderValueChanged(newPos / 4);
		oldPos = newPos / 4;
	}
}

void Menu::encoderButtonClicked()
{
    if (manager.settings->getByIndex(currentItemSelected).getType() == Xylitol::ValueType::Action)
    {
        manager.settings->getByIndex(currentItemSelected).exec();
    }

	changingValue = !changingValue;
	if (changingValue)
	{
		encoderInput.write(manager.settings->getByIndex(currentItemSelected).getValue());
	}
	else
	{
		encoderInput.write(currentItemSelected * 4);
	}
	currentItemChanged = currentItemSelected;
}

void Menu::setLedRingValue(const uint8_t &value, bool bottomLedOn = false)
{
	digitalWrite(RING_LE, LOW);

	if (bottomLedOn == 0)
		shiftOut(RING_SDI, RING_CLK, MSBFIRST, (ledRingSeq[value] | 0x8000) >> 8);
	else
		shiftOut(RING_SDI, RING_CLK, MSBFIRST, (ledRingSeq[value]) >> 8);
	shiftOut(RING_SDI, RING_CLK, MSBFIRST, ledRingSeq[value]);
	digitalWrite(RING_LE, HIGH);
}

void Menu::encoderValueChanged(const int32_t &encoderValue)
{
	if (changingValue)
	{
		if (encoderValue > oldPos)
		{
			auto &s = manager.settings->getByIndex(currentItemSelected);
			s++;
		}
		else
		{
			auto &s = manager.settings->getByIndex(currentItemSelected);
			s--;
		}
	}
	else
	{
		currentItemSelected = encoderValue;

		if (currentItemSelected < 0)
		{
			currentItemSelected = (int32_t) manager.settings->getNumSettings() - 1;
			encoderInput.write(((int32_t) manager.settings->getNumSettings() - 1) * 4);
		}
		if (currentItemSelected > (int32_t) manager.settings->getNumSettings() - 1)
		{
			currentItemSelected = 0;
			encoderInput.write(0);
		}
	}
}