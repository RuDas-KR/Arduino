void setup()
{
    Serial.begin(9600);
    Serial.println(digitalRead(28));
}

void loop()
{
  if(digitalRead(28) == 0)
    Serial.println("Pressed");
    
  else
    Serial.println("UnPressed");
}
