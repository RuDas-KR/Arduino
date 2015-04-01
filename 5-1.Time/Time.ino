#include <Time.h>

void setup() {
  Serial.begin(9600);
  setTime(23,59,0,19,2,14);
}

void loop() {
  digitalClockDisplay();
  delay(500);
}

void digitalClockDisplay() {
  Serial.print(year());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print("; ");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
