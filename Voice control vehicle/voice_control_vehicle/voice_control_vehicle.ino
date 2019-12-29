#include "String.h"
#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1);
String readvoice, cmd;
int spd = 80, dla = 100;

String  command[20]={"forward","go", "stop", "left", "left 30", "right", "right 30", "back", "back turn", "speed up", "speed down"};

//==================Motor Driver Pin===================
const int inA = 11 , inB = 10, inC = 6, inD = 5;
int lastSpeedL, lastSpeedR;
int leftSign, rightSign;

//=================Sonar Pin========{tigr, echo}=======
int leftSonarPin[2] = {12, 9}, forwardSonarPin[2] = {12, 8}, rightSonarPin[2] = {12, 3}, backSonarPin[2] = {12, 4};
float leftSonar, forwardSonar, rightSonar, backSonar;


void setup() {
  pinMode(2, OUTPUT);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(forwardSonarPin[0], OUTPUT);
  pinMode(forwardSonarPin[1], INPUT);
  pinMode(leftSonarPin[1], INPUT);
  pinMode(rightSonarPin[1], INPUT);
  pinMode(backSonarPin[1], INPUT);



  beep(100);
  delay(200);
  beep(100);
  delay(200);
  beep(400);
  BT.begin(9600);
  Serial.begin(9600);
}

void loop() 
  {
    while (BT.available()){  //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    cmd += c; //build the string- "forward", "reverse", "left" and "right"
    } 
    if(cmd != "")
      readvoice = cmd;
    if (readvoice.length() > 0) {
      Serial.println(readvoice);
      Serial.println(cmd);
  
    if(readvoice == "forward")
    {
      forwardSonar = sonarRead(forwardSonarPin);
      if(forwardSonar > 30 || forwardSonar == 0){
        motor(spd,spd);
        delay(dla);
      } 
      else
        beep(100);
    }
  
    else if(readvoice == "back")
    {
      backSonar = sonarRead(backSonarPin);
      if(backSonar > 30 || backSonar == 0){
        motor(-spd,-spd);
        delay(dla);
      }
      else
        beep(100);      
    }
  
    else if (readvoice == "left")
    {
      leftSonar =  sonarRead(leftSonarPin);
      if(leftSonar > 30 || leftSonar == 0){
        motor(-spd,spd);
        delay (8*dla);
        brk(30);
        readvoice = "forward";
      }
      else
        beep(100);
    }
  
   else if ( readvoice == "right")
   {
     rightSonar =  sonarRead(rightSonarPin);
     if(rightSonar > 30 || leftSonar == 0){
       motor(spd,-spd);
       delay (8*dla);
       brk(30);
       readvoice = "forward";
     }
     else
        beep(100);
   }
  
   else if (readvoice == "stop")
   {
     brk(60);
   }
   else if (readvoice == "round")
   {
     motor(spd,-spd);
     delay (30*dla);
     brk(30);
   }
  }
  else if(readvoice == "speed up")
  {
    spd += 20;
    dla -= 20;
  }
  else if(readvoice == "speed down")
  {
    spd -= 20;
    dla += 20;
  }
  cmd="";
}


//+++++++++++++++++++++++ COMMAND +++++++++++++++++++++++++++++++++++


//+++++++++++++++++ beep funciton +++++++++++++++++++
void beep(int a){
  digitalWrite(2, 1);
  delay(a);
  digitalWrite(2, 0);
}

//++++++++++++++++++ Motor Driver +++++++++++++++++++++++++
void motor(int left, int right) {
  int a = 0, b = 0, c = 0, d = 0;
  lastSpeedL = left;
  lastSpeedR = right;

  if (left > 0)a = left;
  else b = left * -1;
  if (right > 0)c = right;
  else d = right * -1;
  analogWrite(inA, a);
  analogWrite(inB, b);
  analogWrite(inC, c);
  analogWrite(inD, d);
}
//++++++++++++++++++ break function +++++++++++++++++++
void brk(int a) {
  motor(-lastSpeedL, -lastSpeedR);
  delay(a);
  motor(0, 0);
}

//+++++++++++++++++++++++ Sonar Read ++++++++++++++++++++++++++++++
float sonarRead(int pin[2]) {
  float duration, lengthCM = 0;
  digitalWrite(pin[0], LOW);
  delayMicroseconds(2);
  digitalWrite(pin[0], HIGH);
  delayMicroseconds(10);
  digitalWrite(pin[0], LOW);
  duration = pulseIn(pin[1], HIGH,  3000);
  lengthCM = duration / 58.2;
  return lengthCM;
}

