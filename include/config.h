#pragma once

#include <TimerOne.h>
#include <WS2812Serial.h>
#include <LedControl.h>
#include <ResponsiveAnalogRead.h>
#include <functional>
#include <Bounce2.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

#define MATRIX_DATA  32
#define MATRIX_CLK   30
#define MATRIX_LOAD  31
#define MATRIX_NUM   2

#define WS2812_PIN   35
#define WS2812_COUNT 10

#define POT_COUNT    8
#define POT_SLEEP    true

#define BUTTON0      28
#define BUTTON1      29
#define BUTTON2      33
#define BUTTON3      34
#define BUTTON4      9

#define LED_BUTTON4 14
#define ENCODER_A   36
#define ENCODER_B   37
#define ENCODER_BTN 2

#define RING_SDI    4
#define RING_CLK    3
#define RING_LE     5

#define GRANULAR_MEMORY_SIZE 12800 * 2
#define FLANGE_DELAY_LENGTH (4*AUDIO_BLOCK_SAMPLES)

#define SEQ_MAX_TRACKS          8
#define SEQ_MAX_STEPS_PER_TRACK 16
#define CLOCKS_PER_BEAT 24
#define QUARTER_NOTE 1
#define EIGHTH_NOTE  2
#define SIXTEENTH_NOTE 4