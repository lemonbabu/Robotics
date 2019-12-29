//pin declation
int bzr = 12, wtr = A2, snr[2]={3,2}, ldr = A1;

void setup() {
  // put your setup code here, to run once:
  pinMode(wtr, INPUT);
  pinMode(bzr, OUTPUT);
  pinMode(snr[0], OUTPUT);
  pinMode(snr[1], INPUT);
  pinMode(ldr, INPUT);
  
  beep(100);
  delay(100);
  beep(200);
  Serial.begin(9600);
}

void loop() {
  int object = sonarRead(snr);
  int water = digitalRead(wtr);
  int ldrread = digitalRead(ldr);
  
  if(object != 0 && object <= 29){
    beep(200);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
  }
  else if(water == 1){
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
    delay(100);
    beep(100);
  }
  else if( ldrread == 1){
    beep(100);
    delay(100);
    beep(100);
    delay(500);
  }
  
  delay(500);
}


//++++++++++++++++functions++++++++++++++++++++
void beep(int a)
{
  digitalWrite(bzr,1);
  delay(a);
  digitalWrite(bzr,0);
}



//////////////////Sonar Read/////////////////////////
float sonarRead(int pin[2]) {
  float duration, lengthCM = 0;
  digitalWrite(pin[0], LOW);
  delayMicroseconds(5);
  digitalWrite(pin[0], HIGH);
  delayMicroseconds(10);
  digitalWrite(pin[0], LOW);
  duration = pulseIn(pin[1], HIGH,  3000);
  lengthCM = duration / 58.2;
  return lengthCM;
}

