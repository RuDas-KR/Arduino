const int LED[] = {24,25,26,27};

void setup(){
  int i;
  for(i=0; i<4; i++){
    pinMode(LED[i], OUTPUT);
  }
}

void loop(){
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
