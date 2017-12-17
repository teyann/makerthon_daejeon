#include "config.h"
#include "led.h"
#include "remote.h"
#include "lcd.h"
#include "ledMatrix.h"
#include "_servo.h"
#include "buzzer.h"

static const String lcdBase = "Culture Court";
static const String lcdStr[5] =
{
  "SPORT", "ART", "MAKER", "FOOD TRUCK", "EVENT"
};

static const uint8_t dotMap[5][8] =
{
  {
    0b00000000,
    0b01000010,
    0b11000011,
    0b11111111,
    0b11111111,
    0b11000011,
    0b01000010,
    0b00000000
  },
  {
    0b00011000,
    0b00010100,
    0b00010010,
    0b00010010,
    0b00010000,
    0b01110000,
    0b01110000,
    0b01110000
  },
  {
    0b00010000,
    0b00111000,
    0b00011100,
    0b00011110,
    0b00111111,
    0b01110010,
    0b11100000,
    0b01000000
  },
  {
    0b00111100,
    0b01000010,
    0b10000001,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00000000
  },
  {
    0b11111111,
    0b11111001,
    0b11111001,
    0b11100111,
    0b11100111,
    0b10011111,
    0b10011111,
    0b11111111
  }
};

enum ledColor
{
  RED ,
  GREEN,
  BLUE,
  NONE,
  MAGENTA
};

uint8_t remoteValue = EVENT; // default

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  randomSeed(analogRead(0));
  initLed();
  writeLed(remoteValue);
  initRemote();
  initLcd();
  writeLcd(lcdBase, lcdStr[remoteValue]);
  initLedMatrix();
  writeLedMatrix(dotMap[remoteValue]);
  initServo();
  initBuzzer();
}

void loop()
{
  static uint8_t preValue = remoteValue;
  uint8_t temp = readRemote();
  uint8_t btnChanged = 0;
  uint8_t stateChanged = 0;

  preValue = remoteValue;

  // button is pushed
  if (temp != DUMMY_DATA)
  {
    btnChanged = 1;
    remoteValue = temp;
#ifdef DEBUG
    Serial.print("Butten is pushed : ");
    Serial.print("value = ");
    Serial.println(remoteValue);
#endif
  }

  // state is changed
  if (preValue != remoteValue)
  {
    stateChanged = 1;
#ifdef DEBUG
    Serial.print("State is changed : ");
    Serial.print("prevalue = ");
    Serial.print(preValue);
    Serial.print(" | value = ");
    Serial.println(remoteValue);
#endif
    writeLed(remoteValue);
    writeLcd(lcdBase, lcdStr[remoteValue]);
    writeLedMatrix(dotMap[remoteValue]);
  }

  // button is pushed
  if (btnChanged == 1)
  {
    // Event
    if(remoteValue == EVENT)
    {
      for(uint8_t i = 0; i < 5; i++)
      {
        writeServo(random(180));
        delay(333);
      }
      writeServo(random(180));
    }
  }

  if (stateChanged == 1)
  {
    // Art
    if(remoteValue == ART)
    {
      singBuzzer();
    }
    if(preValue == EVENT)
    {
      writeServo(90); // default
    }
  }
  delay(50);
}

static void writeLed(ledColor color)
{
  Serial.print("LED Color = ");
  switch(color)
  {
    case RED: // SPORT
    writeLedRGB(0xFF, 0x00, 0x00);
    
    writeLed1(HIGH);
    writeLed2(LOW);
    writeLed3(LOW);
#ifdef DEBUG
    Serial.println("RED");
#endif
    break;

    case GREEN: // ART
    writeLedRGB(0x00, 0xFF, 0x00);

    writeLed1(LOW);
    writeLed2(HIGH);
    writeLed3(LOW);
#ifdef DEBUG
    Serial.println("GREEN");
#endif
    break;

    case BLUE: // MAKER
    writeLedRGB(0x00, 0x00, 0xFF);
    
    writeLed1(LOW);
    writeLed2(LOW);
    writeLed3(HIGH);
#ifdef DEBUG
    Serial.println("BLUE");
#endif
    break;

    case MAGENTA: // EVENT
    writeLedRGB(0xFF, 0x00, 0xFF);
#ifdef DEBUG
    Serial.println("BLUE");
#endif
    break;

    default:
    writeLedRGB(0x00, 0x00, 0x00);
#ifdef DEBUG
    Serial.println("NONE/UNDEFINED");
#endif
    break;
  }
}

