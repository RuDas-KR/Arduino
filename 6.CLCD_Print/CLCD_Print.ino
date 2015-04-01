#include <LiquidCrystal.h>

LiquidCrystal lcd(40, 54, 41, 42, 43, 44, 45);

void setup() {
  lcd.begin(8,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(4,1);
  lcd.print("TEST");
}

void loop() {
}
