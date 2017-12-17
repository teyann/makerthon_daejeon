#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "lcd.h"

LiquidCrystal_I2C lcd(0x3F,16,2);

void initLcd()
{
  lcd.init();
  lcd.backlight();
}

void writeLcd(String line1, String line2)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}
