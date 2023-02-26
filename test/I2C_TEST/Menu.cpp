#include <LiquidCrystal.h>
#include <Arduino.h>

#include "Menu.h"

LiquidCrystal lcd(10,3,4,5,6,7);

byte clockChar[8] = {
  B11111,
  B01010,
  B01010,
  B00100,
  B01010,
  B01010,
  B11111,
  B00000,
};

byte readyChar[8] = {
  B00000,
  B11011,
  B01010,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000
};

String readyMessage = "ready to start";

void display_basic_menu(uint8_t customChar, String message, String prompt) {
  lcd.begin(16,2);
  lcd.createChar(0, customChar);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.print(message);
  lcd.write(byte(0));

  lcd.setCursor(0,1);
  lcd.print(prompt);
}



void initial_menu() {
  display_basic_menu(clockChar, "GRP 07 B ACE1", "Starting");
}

void ready_menu() {
  display_basic_menu(readyChar, "ready to start", "Press x for menu");
}

// Scroll the message across the display
