#include <LiquidCrystal.h>
#include "Menu.h"


LiquidCrystal lcd(2,3,4,5,6,7); // RS, E, D4, D5, D6, D7

clockChar[8] = {
  
  B11111,
  B01010,
  B01010,
  B00100,
  B01010,
  B01010,
  B11111,
  B00000,
};

readyChar[8] = {
  B00000,
  B11011,
  B01010,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup() {
  lcd.createChar(0,clockChar);
  lcd.begin(16,2);
  lcd.write(byte(0));
  lcd.print("GPR 07 B ACE1");
  lcd.write(byte(0));
  lcd.setCursor(0,1);
  lcd.print("starting");

}

void loop() { 
}