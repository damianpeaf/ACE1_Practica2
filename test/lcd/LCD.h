#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void lcd_init() {
  lcd.begin(16, 2);
}

void lcd_print(String text) {
  lcd.clear();
  lcd.print(text);
}