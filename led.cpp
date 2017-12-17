#include <Arduino.h>
#include "led.h"

#define IS_HIGH(X) ((X == 0xFF) ? (HIGH) : (LOW))

#define NUM_LED 3

static const uint8_t rgbLedMap[NUM_LED] =
{
  4, 3, 8
};

static const uint8_t ledMap[NUM_LED] =
{
  6, 7, A1
};

enum ledInColor
{
  IN_RED,
  IN_GREEN,
  IN_BLUE
};

void initLed()
{
  for(uint8_t i = 0; i < NUM_LED; i++) // rgb Led
  {
    pinMode(rgbLedMap[i], OUTPUT);
    pinMode(ledMap[i], OUTPUT);
  }
}

void writeLedRGB(uint8_t r, uint8_t g, uint8_t b)
{
  digitalWrite(rgbLedMap[ledInColor::IN_RED], IS_HIGH(r));
  digitalWrite(rgbLedMap[ledInColor::IN_GREEN], IS_HIGH(g));
  digitalWrite(rgbLedMap[ledInColor::IN_BLUE], IS_HIGH(b));
}

void writeLed1(uint8_t on)
{
  digitalWrite(ledMap[0], on);
}
void writeLed2(uint8_t on)
{
  digitalWrite(ledMap[1], on);
}
void writeLed3(uint8_t on)
{
  digitalWrite(ledMap[2], on);
}

