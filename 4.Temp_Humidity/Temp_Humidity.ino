#include <SHT1x.h>

#define dataPin 22
#define clockPin 23
SHT1x sht1x(dataPin, clockPin);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Up");
}

void loop() {
  float temp_c;
  float temp_f;
  float humidity;
  
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
  
  Serial.print("Temperature: ");
  Serial.print(temp_c, DEC);
  Serial.print("C / ");
  Serial.print(temp_f, DEC);
  Serial.print("F. Humidity ");
  Serial.print(humidity);
  Serial.println("%");
  delay(500);
}
