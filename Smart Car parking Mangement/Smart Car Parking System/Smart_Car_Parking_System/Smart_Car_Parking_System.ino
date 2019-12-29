#include <LiquidCrystal.h>
#include<Servo.h>

// initialize the library with the numbers of the interface pins
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int senArrPin[6] = {A0, A1, A2, A3, A4, A5};
int sen[6] = {0};
int lcdcnt = 0, ldrPin[2] = {3, 2}, ldrIn = 0, ldrOut = 0;
long int full = 0, prefull;
//servo
Servo servoIn, servoOut;


// declation of pin setup 
void setup() {
  //servo
  servoIn.attach(5);
  servoOut.attach(4);
  servoIn.write(0);
  servoOut.write(90);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome");

  //sensor pin mode
  pinMode(ldrPin[0], INPUT);
  pinMode(ldrPin[1], INPUT);
  for (int i = 0; i < 6; i++)
    pinMode(senArrPin[i], INPUT);

  Serial.begin(9600);
}


// main loop of this program
void loop() {
  sensorRead();
  dspl();

  if (ldrIn == 0 && full != 123456)
  {
    servoIn.write(90);
    delay(5000);
  }
  else if (ldrOut == 0)
  {
    servoOut.write(0);
    delay(5000);
  }
  else {
    servoIn.write(0);
    servoOut.write(90);
  }

}



//++++++++++++++++++++Sensors read++++++++++++++++++++
void sensorRead()
{
  full = 0;
  for (int i = 0; i < 6; i++)
  {
    sen[i] = (((analogRead(senArrPin[i])) > 250) ? 1 : 0);
  }
  full =  (long int)(sen[0]*100000 + sen[1]*20000 + sen[2]*3000 + sen[3]*400 + sen[4]*50 + sen[5]*6);
  ldrIn = (digitalRead(ldrPin[0]));
  ldrOut = (digitalRead(ldrPin[1]));

}


// This funtion for showing result in display
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


