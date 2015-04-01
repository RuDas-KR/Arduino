#include <LiquidCrystal.h>
#include <SHT1x.h>
#include "Wire.h"

#define DS1307_ADDRESS 0x68
#define dataPin 22
#define clockPin 23
SHT1x sht1x(dataPin, clockPin);

LiquidCrystal lcd(40, 54, 41, 42, 43, 44, 45);

void setup(){
  Wire.begin();
  Serial.begin(9600);
  setDateTime(); //MUST CONFIGURE IN FUNCTION
  lcd.begin(8,2);
}

void loop(){
  printDate();
  delay(1000);
}

void setDateTime(){

  byte second =      45; //0-59
  byte minute =      40; //0-59
  byte hour =        0; //0-23
  byte weekDay =     2; //1-7
  byte monthDay =    1; //1-31
  byte month =       3; //1-12
  byte year  =       11; //0-99

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write((byte)0); //stop Oscillator

  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(monthDay));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));

  Wire.write((byte)0); //start 

  Wire.endTransmission();

}

byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

void printDate(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write((byte)0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());

  //print the date EG   3/1/11 23:59:59
  
  lcd.clear();
  lcd.setCursor(0.0);
  lcd.print("

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(month);
  lcd.setCursor(1,0);
  lcd.print("/");
  lcd.setCursor(2,0);
  lcd.print(monthDay);
  lcd.setCursor(0,1);
  lcd.print(hour);
  lcd.setCursor(1,1);
  lcd.print(":");
  lcd.setCursor(2,1);
  lcd.print(minute);
  lcd.setCursor(4,1);
  lcd.print(":");
  lcd.setCursor(5,1);
  lcd.print(second);
}
