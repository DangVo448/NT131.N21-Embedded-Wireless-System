#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>

int relay=2;
int cb=4;
int coi=14;
int gtcb;
//SoftwareSerial mega(D5,D6);//tx-6, rx-5
char auth[] = "Db-HdHI7AGjWczhm12dixZwTOlvlIEyZ"; //YourToken
// Your WiFi credentials.
char ssid[] = "T3.10 T3.11"; //YourNetworkName
char pass[] = "Tanvubuilding01"; //YourPassword
BlynkTimer timer; 

//////////////////


void setup()
{
  // Debug console
  pinMode(cb,INPUT);
  pinMode(relay,OUTPUT);
  pinMode(coi,OUTPUT);
}