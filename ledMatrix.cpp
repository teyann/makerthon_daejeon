#include <Arduino.h>
#include "LedControl.h"
#include "config.h"
#include "ledMatrix.h"

LedControl ledMatrix(12,10,11,1);

void initLedMatrix()
{
  ledMatrix.shutdown(0,false);
  /* Set the brightness to a medium values */
  ledMatrix.setIntensity(0,8);
  /* and clear the display */
  ledMatrix.clearDisplay(0);
}

void writeLedMatrix(uint8_t *matrixMap)
{
  for (int i = 0; i < 8; i++)  
  {
    ledMatrix.setRow(0,i,matrixMap[i]);
  }
}
