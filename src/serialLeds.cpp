#include "serialLeds.hpp"

DMAMEM byte displayMemory[WS2812_COUNT*12];
byte drawingMemory[WS2812_COUNT*3];
using namespace Xylitol;
int spectrum[10] = {
		0x000004,
		0x000008,
		0x000400,
		0x000800,
		0x040400,
		0x080800,
		0x090900,
		0x020000,
		0x040000,
		0x080000
		};

SerialLeds::SerialLeds(Manager &_manager) : manager(_manager)
{

}

void SerialLeds::begin()
{
	counter = 0;
	leds = new WS2812Serial(WS2812_COUNT, displayMemory, drawingMemory, WS2812_PIN, WS2812_GRB);
	leds->begin();
	for(int i=0; i<WS2812_COUNT; i++) {
		leds->setPixel(i, i + 8);
		leds->show();
		delay(25);
	}
}

void SerialLeds::update(const float peakValue)
{
	leds->clear();
	const int v = 10 * peakValue;
	for (int i=0; i<v; i++)
	{
		leds->setPixel(i, spectrum[i]);
	}
	leds->show();
}