// include the library code:
#include <LiquidCrystal.h>
#include<Servo.h>

Servo servoIn, servoOut;
int ldrIn = 3, ldrOut = 4;
int car ;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(ldrIn, INPUT);
  pinMode(ldrOut, INPUT);
  
  servoIn.attach(5);
  servoOut.attach(4);
  servoIn.write(0);
  servoOut.write(90);
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {

  int carIn, carOut;
  carIn = digitalRead(ldrIn);
  carOut = digitalRead(ldrOut);

  if(carIn == 0 && car < 2)
    {
      servoIn(120);
      delay(10000);
      servoIn(0);
      car++;
      dis();
    }
    if(carOut == 0){
      servoOut(120);
      delay(10000);
      servoOut(0);
      car--;
      dis();
    }
}

void dis(){
  lcd.clear();
  if(car == 0){
    lcd.print("No parking slot free");
  }
  else{
    lcd.print(car + " slot free");
  }
  
}
