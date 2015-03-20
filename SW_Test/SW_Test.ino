const int LED1 = 24;
const int LED2 = 25;
const int LED3 = 26;
const int LED4 = 27;

const int SW1 = 28;
const int SW2 = 29;
const int SW3 = 30;
const int SW4 = 31;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
}

void loop() {
 if(digitalRead(SW1) == HIGH)
   digitalWrite(LED1, HIGH);
 else
   digitalWrite(LED1, LOW); // LED1
   
 if(digitalRead(SW2) == HIGH)
   digitalWrite(LED2, HIGH);
 else
   digitalWrite(LED2, LOW); // LED2
   
 if(digitalRead(SW3) == HIGH)
   digitalWrite(LED3, HIGH);
 else
   digitalWrite(LED3, LOW); // LED3
   
 if(digitalRead(SW4) == HIGH)
   digitalWrite(LED4, HIGH);
 else
   digitalWrite(LED4, LOW); //LED4
}
