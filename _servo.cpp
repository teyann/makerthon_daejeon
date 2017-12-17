#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "_servo.h"

#define SERVO_PIN 5

Servo myservo;

void initServo()
{
  myservo.attach(SERVO_PIN);
  myservo.write(90); // initial degree
}

void writeServo(uint8_t deg)
{
  myservo.write(deg);
}

