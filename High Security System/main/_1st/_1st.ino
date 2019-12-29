#include "Keypad.h"
#include "U8glib.h"
#include "Servo.h"
#include "String.h"

//PIN initialization 

int pinOlcd[2] = {A4,A5};
int pinIR = A0;
int pinBzr = 13;
int pinLDR = 12;
int pinServo = 11;
int pinBtn = 10;
//+++++dipaly+++++
char ADCval[5];
int adcval;
U8GLIB_SSD1306_128X64 lcd(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  

//+++++keypad+++++
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {8, 2, 3, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 6, 7}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

 
//+++++++++++++++++++Variable+++++++++++++++++++++

int ir, ldr, btn , door = 0, k = 0;
Servo servo;
String key = "****", pass = "1234";
char buf[5];


 //++++++++++++++++++++functions+++++++++++++++++++++

void sensorRead(){
    if(analogRead(pinIR) > 100)
      ir = 1;
    else 
      ir = 0;
  ldr = digitalRead(pinLDR);
  btn = digitalRead(pinBtn);
  char keys = keypad.getKey();
  if (keys != NO_KEY){
    key[k++] = keys;
    key.toCharArray(buf, 5);
    if(k == 4){
      k = 0;
      if(key != pass)
      {
        beep(300);
        key = "Wrong";
        key.toCharArray(buf, 6);
        dspl();
        delay(1000);
        key = "****";
        key.toCharArray(buf, 5);
        door = 1;
      }
    }
  }
}
void beep(int a){
  digitalWrite(pinBzr,HIGH);
  delay(a);
  digitalWrite(pinBzr,LOW);
}

void draw(void) 
{
  lcd.setFont(u8g_font_osb18);
  lcd.drawStr( 20, 20, "DUET");
  lcd.drawHLine (10,25,100);
  lcd.setFont(u8g_font_unifont);
  lcd.drawStr( 5, 40, "Enter Password");
  lcd.setFont(u8g_font_osb18);
  lcd.drawStr( 30, 60, buf);
}

void dspl(){
///display code
  lcd.firstPage(); 
  do {draw();} while( lcd.nextPage() );
  delay(50);
}

//++++++++++++++++++++++ void setup ++++++++++++++++++++++++++=
void setup() {
  key.toCharArray(buf, 5);
  
  servo.attach(11);
  pinMode(pinIR, INPUT);
  for(int i = 1; i < 8; i++)
    pinMode(i, INPUT);
  pinMode(pinBzr, OUTPUT);
  pinMode(pinLDR, INPUT);
  pinMode(pinServo, OUTPUT);
  pinMode(pinBtn, INPUT);

  //lcd.setRot180();   // flip screen, if required
  lcd.setColorIndex(1); // 1 for monochrome

  servo.write(103);
  beep(200);
  delay(100);
  beep(100);
  Serial.begin(9600);
}

//+++++++++++++++++ main loop +++++++++++++++++++++++++++
void loop() {
  // put your main code here, to run repeatedly:
  sensorRead();
  dspl();
  if(ldr == 0)
  {
    door = 0;
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
    delay(100);
  }
  else if(ir == 1 && door == 1){
    door = 0;
    servo.write(103);
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    key = "Close";
    key.toCharArray(buf, 6);
    dspl();
    delay(1000);
    key = "****";
    key.toCharArray(buf, 5);
  }
  else if(key == pass)
  {
    servo.write(9);
    key = "Open";
    key.toCharArray(buf, 5);
    dspl();
    delay(1000);
    key = "****";
    key.toCharArray(buf, 5);
    door = 1;
  }
  else if(btn == 1 && door == 0){
    servo.write(9);
    door = 1;
    key = "Open";
    key.toCharArray(buf, 6);
    dspl();
    delay(2000);
    key = "****";
    key.toCharArray(buf, 5);
    delay(5000);
    servo.write(103);
    door = 1;
  }
}

