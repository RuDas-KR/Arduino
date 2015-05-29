#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(40, 54, 41, 42, 43, 44, 45);

#define  btn1  28 //모드선택기능
#define  btn2  29 //FND 숫자 업 버튼
#define  btn3  30 //FND 숫자 다운 버튼
#define  btn4  31 //FND 0으로 초기화버튼
#define  US  15
#define DS1307_ADDRESS 0x68

const int ledPin[4] = {24, 25, 26, 27};
const int lookup[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

unsigned char mode = 3;
unsigned long duration;
int mode_cnt = 0, mode_cnt1 = 0, mode_cnt2 = 0, count, count1, count2, count3, pw, pw1, pw2, pw3, cnt = 0, dummcnt, Distance, Temp;

void setup() 
{
  int i;
  
  lcd.begin(8,2);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  
  pinMode(US, OUTPUT);
  digitalWrite(US, LOW);
  
  for(i=0; i<4; i++)
  {
    pinMode(ledPin[i], OUTPUT);
  }
  Wire.begin();
  setDateTime();
}

void loop() {
  display_mode();
  delay(250);
}

void setDateTime()
{         //초기 시간 설정
  byte second =      40; //0-59
  byte minute =      30; //0-59
  byte hour =        12; //0-23
  byte weekDay =     1; //1-7
  byte monthDay =    22; //1-31
  byte month =       5; //1-12
  byte year  =       15; //0-99

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
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
  return ( (val/16*10) + (val%16) );
}

void display_mode() //1버튼으로 모드설정
{
  if(digitalRead(btn1)==0)	mode_cnt++;
  
  switch(mode_cnt) {
    case 0: count_mode(); sonic();  break;
    case 1: pw_mode();  break;
  }
  
  if(mode_cnt>1) mode_cnt=0;
}

void count_mode() //2버튼으로 count FND 모드설정
{
  if(digitalRead(btn2)==0) mode_cnt1++;
  
  switch(mode_cnt1) {
    case 0: one(); LED0();  break;
    case 1: two(); LED1(); break;
    case 2: three(); LED2(); break;
    case 3: four(); LED3(); break; 
  }
  
  if(mode_cnt1>3) mode_cnt1=0;
}

void sonic() //초음파 거리로 LCD표현
{
   delay(500);
   pinMode(US, OUTPUT);
   digitalWrite(US, HIGH);
   delayMicroseconds(10);
   digitalWrite(US, LOW);
   
   pinMode(US, INPUT);
   duration = pulseIn(US, HIGH);
   
   Distance = (331.5 + 0.607 * 25) * ( duration * 0.001 / 2 )/10;
   
   if (Distance <= 15) //15cm 이하 일 경우 LCD
   {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Hello");
     play();
   } else if (Distance >15 && Distance <=40)
   {         // 15cm 초과 40cm 이하 일 경우 LCD
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Come");
   count=0;
   count1=0;
   count2=0;
   count3=0;
 }
 else //40cm 초과 할 경우 LCD
    {
      printDate();
      count=0;
      count1=0;
      count2=0;
      count3=0;
    }
}

void pw_mode() //2버튼으로 pw FND 모드설정
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PassWord");
  lcd.setCursor(0,1);
  lcd.print("Setting");
  
  if(digitalRead(btn2)==0) mode_cnt2++;
    
  switch(mode_cnt2) {
    case 0: one1(); LED0();  break;
    case 1: two1(); LED1(); break;
    case 2: three1(); LED2(); break;
    case 3: four1(); LED3(); break; 
  }
  if(mode_cnt2>3) mode_cnt2=0;
}

void play() //count와 pw를 비교하여 LCD표시
{ 			//count와 pw가 같으면 열림
  if (count == pw && count1 ==pw1 && count2 ==pw2 && count3 ==pw3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome");
    lcd.setCursor(0,1);
    lcd.print("open");
  }
  else   //count와 pw가 다르면 닫힘
  {
    lcd.setCursor(0,1);
    lcd.print("close");
  }
}

void printDate()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write((byte)0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111);
  int weekDay = bcdToDec(Wire.read()); 
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());

  lcd.begin(8,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(year);
  lcd.setCursor(2,0);
  lcd.print("Y");
  lcd.setCursor(3,0);
  lcd.print(month);
  lcd.setCursor(5,0);
  lcd.print("-");
  lcd.setCursor(6,0);
  lcd.print(monthDay);
  lcd.setCursor(0,1);
  lcd.print(hour);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(minute);
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(second);
}

void LED0()
{
    digitalWrite(ledPin[0],LOW);
    digitalWrite(ledPin[1],HIGH);
    digitalWrite(ledPin[2],HIGH);
    digitalWrite(ledPin[3],HIGH);
}
void LED1()
{
    digitalWrite(ledPin[0],HIGH);
    digitalWrite(ledPin[1],LOW);
    digitalWrite(ledPin[2],HIGH);
    digitalWrite(ledPin[3],HIGH);
}
void LED2()
{
    digitalWrite(ledPin[0],HIGH);
    digitalWrite(ledPin[1],HIGH);
    digitalWrite(ledPin[2],LOW);
    digitalWrite(ledPin[3],HIGH);
}
void LED3()
{
    digitalWrite(ledPin[0],HIGH);
    digitalWrite(ledPin[1],HIGH);
    digitalWrite(ledPin[2],HIGH);
    digitalWrite(ledPin[3],LOW);
}

void Wire_init()
{
  Wire.beginTransmission(0x38);
  Wire.write((byte)0);
  Wire.write(B01000111);
  Wire.endTransmission();
}

void wire_lookup()
{
  Wire.beginTransmission(0x38);
  Wire.write((byte)1);
  Wire.write(lookup[count]);
  Wire.write(lookup[count1]);
  Wire.write(lookup[count2]);
  Wire.write(lookup[count3]);
  Wire.endTransmission();
}

void wire_lookuppw()
{
   Wire.beginTransmission(0x38);
   Wire.write((byte)1);
   Wire.write(lookup[pw]);
   Wire.write(lookup[pw1]);
   Wire.write(lookup[pw2]);
   Wire.write(lookup[pw3]);
   Wire.endTransmission();
 }

void one()
{
  Wire_init();
  
  if(count>=10) {
    count=0;
  }
  
  else if(digitalRead(btn3)==0) {
    count++;
  }
  
  if(count<0) {
    count=9;
  }
  else if(digitalRead(btn4)==0 {
    count--;
  }
  
  wire_lookup();
}

void two()
{
  Wire_init();
  
  if(count1>=10) {
    count1=0;
  }
  
  else if(digitalRead(btn3)==0) {
    count1++;
  }
  
  if(count1<0) {
    count1=9;
  }
  else if(digitalRead(btn4)==0) {
    count1--;
  }
  
  wire_lookup();
}

void three()
{
  Wire_init();
  
  if(count2>=10) {
    count2=0;
  }
  
  else if(digitalRead(btn3)==0) {
    count2++;
  }
  
  if(count2<0) {
    count2=9;
  }
  else if(digitalRead(btn4)==0) {
    count2--;
  }
  
  wire_lookup();
}

void four()
{
  Wire_init();
  
  if(count3>=10) {
    count3=0;
  }
  
  else if(digitalRead(btn3)==0) {
    count3++;
  }
  
  if(count3<0) {
    count3=9;
  }
  else if(digitalRead(btn4)==0) {
    count3--;
  }
  
  wire_lookup();
}

void one1() //1번째자리 pw FND
{
  Wire_init();
  
  if(pw>=10) { 
    pw=0;
  }
  else if(digitalRead(btn3)==0) {
    pw++;
  }
  if(pw<0) { 
    pw=9;
  }
  else if(digitalRead(btn4)==0) {
    pw--;
  }
  
    wire_lookuppw();
}

void two1() //2번째자리 pw FND
{
  Wire_init();
  
  if(pw1>=10) { 
    pw1=0;
  }
  else if(digitalRead(btn3)==0) {
    pw1++;
  }
  if(pw1<0) { 
    pw1=9;
  }
  else if(digitalRead(btn4)==0) {
    pw1--;
  }
    wire_lookuppw();
}

void three1() //3번째자리 pw FND
{
  Wire_init();
  
  if(pw2>=10) { 
    pw2=0;
  }
  else if(digitalRead(btn3)==0) {
    pw2++;
  }
  if(pw2<0) { 
    pw2=9;
  }
  else if(digitalRead(btn4)==0) {
    pw2--;
  }
    wire_lookuppw();
}

void four1() //4번째자리 pw FND
{
  Wire_init();
  
  if(pw3>=10) { 
    pw3=0;
  }
  else if(digitalRead(btn3)==0) {
    pw3++;
  }
  if(pw3<0) { 
    pw3=9;
  }
  else if(digitalRead(btn4)==0) {
    pw3--;
  }
    wire_lookuppw();
}