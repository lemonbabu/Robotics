#include<SoftwareSerial.h>

int speed = 255;
char command = '\0';

//////////Motor Driver////////////
int inA=3, inB=2, inC=4, inD=5, enL=6, enR=7;


void setup(){
  for(int i = 2; i < 8; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  command=Serial.read();
      //Serial.println(command);
  if(Serial.available()>0){    
    command=Serial.read();
      if(command=='F')      motor(speed,speed);
        
      else if(command=='B') motor(-speed,-speed);
              
      else if(command=='L') motor(-speed,speed);
              
      else if(command=='R') motor(speed,-speed);
              
      else if(command=='G') motor(0,speed);
              
      else if(command=='I') motor(speed,0);
              
      else if(command=='H') motor(0,-speed);
            
      else if(command=='J') motor(-speed,0);
              
      else if(command=='S') motor(0,0);
            
      else if(command=='0') speed=0;
            
      else if(command=='1') speed=25;
            
      else if(command=='2') speed=50;
            
      else if(command=='3') speed=75;
            
      else if(command=='4') speed=100;
            
      else if(command=='5') speed=125;
            
      else if(command=='6') speed=150;
            
      else if(command=='7') speed=175;
            
      else if(command=='8') speed=200;
            
      else if(command=='9') speed=225;
            
      else if(command=='q') speed=255;
            
      else motor(0,0); 
  }
}

void motor(int left, int right){
  int a=0,b=0;
  a=(left>0)?1:0;
  b=(right>0)?1:0;
  left=(left>0)?left:left*-1;
  right=(right>0)?right:right*-1;
  digitalWrite(inC,b);
  digitalWrite(inD,!b);
  analogWrite(enR,right);
  digitalWrite(inA,a);
  digitalWrite(inB,!a);
  analogWrite(enL,left);
}
