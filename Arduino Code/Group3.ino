
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "hethongbaotrom-b4955-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "4yEge3xYbiZktDtPHpvkHqVWobj48M7U2aaLZrP3"
#define WIFI_SSID "T3.10 T3.11"
#define WIFI_PASSWORD "Tanvubuilding01"

int relay=2;//D4
int cb=4;   //D2

//Define FirebaseESP8266 data object
FirebaseData firebaseData;


FirebaseJson json;


void setup()
{

  Serial.begin(115200);

  
  pinMode(relay,OUTPUT);
  
  pinMode(cb,INPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void sensorUpdate(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = digitalRead(cb);
  Serial.print(F("cb: "));
  Serial.print(h);
  

  if (Firebase.setInt(firebaseData, "/hethongbaotrom/cb", h))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

 
}
void firebasereconnect(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
void loop() {
    sensorUpdate();
    int gtcb = digitalRead(cb);
    if(gtcb==1) digitalWrite(relay,HIGH);
    else digitalWrite(relay,LOW);
    delay(100);
}
