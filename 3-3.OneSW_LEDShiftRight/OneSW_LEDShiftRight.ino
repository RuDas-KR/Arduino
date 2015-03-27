const int LED[] = {24,25,26,27};
const int SW = 28;

void setup(){
  int i;
  for(i=0; i<4; i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(SW, INPUT);
}

void loop(){
  char i;
  if(digitalRead(SW) == LOW){
    while(1){
      for(i=0; i<4; i++){
        digitalWrite(LED[i], HIGH);
        delay(100);
      }
      for(i=0; i<4; i++){
        digitalWrite(LED[i], LOW);
        delay(100);
      }
    }
  }
  
  else{
    for(i=0; i<4; i++){
      digitalWrite(LED[i], HIGH);
    }
  }
}
