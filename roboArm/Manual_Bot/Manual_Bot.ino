#include<SoftwareSerial.h>
#include<Servo.h>

int pos1=0, pos2=0, pos3=0, pos4=0;
char command='\0';
Servo servo1, servo2, servo3, servo4;

//////////Motor Driver////////////


void setup(){

  servo1.attach(6);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
  Serial.begin(9600);
}

void loop(){

  //Serial.println(pos);
  //Serial.println("\n");
  //command = Serial.read();
  //Serial.println(command);
  
  if(Serial.available()>0){
      command=Serial.read();
      //Serial.println(command);
      //Serial.println(pos);
      delay(15);
      pos1 = servo1.read();
      pos2 = servo2.read();
      pos3 = servo3.read();
      pos4 = servo4.read();
      if((command == 'F') && (pos2 < 120)) servo2.write(++pos2);
        
      else if((command == 'B') && (pos2 > 40)) servo2.write(--pos2);
              
      else if(command == 'L' && (pos1 > 20)) servo1.write(--pos1);
              
      else if(command == 'R' && (pos1 < 160)) servo1.write(++pos1);
        
            
      else if(command == 'X') 
      {
        for(pos3, pos4; (pos3<140) && (command != 'x') && (pos4 >20); ++pos3, --pos4)
          {
            command=Serial.read();
            servo3.write(pos3);
            servo4.write(pos4);
            delay(20);
          }
          
      }
      else if(command == 'V') 
      {
        for(pos3, pos4; (pos4<140) && (command != 'v') && (pos3 > 20); --pos3, ++pos4)
          {
            command=Serial.read();
            servo3.write(pos3);
            servo4.write(pos4);
             delay(20);
          }
          
      }

            
  }

}

