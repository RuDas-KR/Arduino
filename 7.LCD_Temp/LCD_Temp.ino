#include <Time.h>
#include <SHT1x.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(40, 54, 41, 42, 43, 44, 45);

#define dataPin 22
#define clockPin 23
SHT1x sht1x(dataPin, clockPin);

void setup() {
  Serial.begin(9600);
  setTime(23,59,0,19,2,14);
  
  lcd.begin(8,2);
}

void loop() {
  float temp_c;
  float temp_f;
  float humidity;
  
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
  delay(500);
  
  lcd.setCursor(0,0);
  lcd.print("TempC");
  lcd.setCursor(5,0);
  lcd.print(temp_c);
  lcd.setCursor(7,0);
  lcd.println("C");
  lcd.setCursor(0,1);
  lcd.print("TempF");
  lcd.setCursor(5,1);
  lcd.print(temp_f);
  lcd.setCursor(7,1);
  lcd.println("F");
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEST");
}
