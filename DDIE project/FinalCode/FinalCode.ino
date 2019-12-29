

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>
#include <NTPClient.h>
#include <WiFiUdp.h>



int n = 0;
String data;
const int light1 = 16, light2 = 5, fan = 4;
float light1Time, light2Time, fanTime; 

//Time
const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Set these to run example.
#define FIREBASE_HOST "intelligent-power-management.firebaseio.com"
#define FIREBASE_AUTH "ibAf2DwCd93xvalQqtrwDGP4b9lE6fD6laXcqJUh"
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "hamid420"


void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin();

  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(fan, OUTPUT);
  
  pinMode(13, OUTPUT);
  pinMode(15, INPUT);
}


//Main loop
void loop() {
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  if(timeClient.getHours()+5 >= 24)
    Serial.print(timeClient.getHours()+5 - 24);
  else 
    Serial.print(timeClient.getHours()+5);
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  
  // put your main code here, to run repeatedly:
 

  data = Firebase.getString("Users/Lemon/mode");
  //Auto mode 
  if (data == "auto"){
      Serial.println("Auto mode is on.");
      
  }
  //Manual Mode 
  else {
    Serial.println("Manual mode is on.");
    data = Firebase.getString("Users/Lemon/devices/light1/light");
    Serial.println(data);
      if(data == "True"){
        digitalWrite(light1, HIGH);
      }
      else{
        digitalWrite(light1, LOW);
      }
      
      data = Firebase.getString("Users/Lemon/devices/light2/light");
      Serial.println(data);
      if(data == "True"){
        digitalWrite(light2, HIGH);
      }
      else{
        digitalWrite(light2, LOW);
      }
      data = Firebase.getString("Users/Lemon/devices/fan1/fan");
      Serial.println(data);
      if(data == "True"){
        digitalWrite(fan, HIGH);
      }
      else{
        digitalWrite(fan, LOW);
      }
  }
  delay(1000);
}



void sensor(){

  
}


