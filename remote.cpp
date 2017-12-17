#include <Arduino.h>
#include <IRremote.h>
#include "remote.h"

#define RECV_PIN 9
#define NUM_REMOTE 6

const uint32_t remoteMap[NUM_REMOTE] = 
{
  0xFF30CF, 0xFF18E7, 0xFF7A85, 0xFF52AD, 0xFF6897, 0xFFFFFF
};

IRrecv irrecv(RECV_PIN);

decode_results results;

#ifdef DEBUG
static const char *remoteCharMap[NUM_REMOTE] =
{
  "1", "2", "3", "9", "0", "\0"
};
#endif

void initRemote()
{
  irrecv.enableIRIn(); // Start the receiver
}

uint8_t readRemote()
{
  uint8_t value = DUMMY_DATA;
  if (irrecv.decode(&results)) {
    for(int i = 0; i < NUM_REMOTE; i++)
    {
      if(remoteMap[i] == results.value)
      {
#ifdef DEBUG
//        Serial.print("char value = ");
//        Serial.print(remoteCharMap[i]);
//        Serial.print(" | int value = ");
//        Serial.println(i);
#endif
        value = i;
      }
    }
    irrecv.resume(); // Receive the next value
  }
  return value;
}

