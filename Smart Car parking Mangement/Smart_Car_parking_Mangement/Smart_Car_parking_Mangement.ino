#include <LiquidCrystal.h>
#include<Servo.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int senArrPin[6] = {A0, A1, A2, A3, A4, A5};
int sen[6] = {0}, ref[6] = {100, 100, 100, 100, 100, 100};
int lcdcnt = 0, ldrPin[2] = {9, 8}, ldrIn = 0, ldrOut = 0;
long int full = 0, prefull;
//servo
Servo servoIn, servoOut;



void setup() {
  //servo
  servoIn.attach(10);
  servoOut.attach(11);
  servoIn.write(0);
  servoOut.write(0);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome");

  //sensor pin mode
  pinMode(ldrPin[0], INPUT);
  pinMode(ldrPin[1], INPUT);
  for (int i = 0; i < 6; i++)
    pinMode(senArrPin[i], INPUT);

  pinMode(12, OUTPUT); 

  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  sensorRead();
  dspl();

  if (ldrIn == 0 && full != 123456)
  {
    servoIn.write(90);
    beep(100);
    delay(5000);
  }
  else if (ldrOut == 0)
  {
    servoOut.write(90);
    beep(100);
    delay(5000);
  }
  else {
    servoIn.write(0);
    servoOut.write(0);
  }

}




////////////////////beep////////////////////////////
void beep(int a){
  digitalWrite(12,HIGH);
  delay(a);
  digitalWrite(12,LOW);
}


//++++++++++++++++++++Sensors read++++++++++++++++++++
void sensorRead()
{
  full = 0;
  for (int i = 0; i < 6; i++)
  {
    sen[i] = (((analogRead(senArrPin[i])) > ref[i]) ? 1 : 0);
  }
  full =  (long int)(sen[0]*100000 + sen[1]*20000 + sen[2]*3000 + sen[3]*400 + sen[4]*50 + sen[5]*6);
  ldrIn = (digitalRead(ldrPin[0]));
  ldrOut = (digitalRead(ldrPin[1]));

}


// display
void dspl()
{
  int all = 0;
  lcd.setCursor(0, 1);
  for (int i = 0; i < 6; i++) {
    if (sen[i] == 0) {
      lcd.print(i + 1);
      lcd.print(", ");
    }
    all += sen[i];
  }
  if (all == 6) {
    lcd.print("No free space");
    lcdcnt = 0;
  }
  else {
    if ((lcdcnt == 0) || (prefull != full)) {
      lcd.clear();
      lcdcnt = 1;
      lcd.print("Welcome");
      prefull   = full;
    }
  }
}

