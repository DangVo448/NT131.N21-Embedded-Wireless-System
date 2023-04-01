
//FirebaseESP8266.h phải được include trước ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Cài đặt thư viện Firebase ESP8266 
#include <ESP8266WiFi.h> // Cài đặt thư viện cho ESP8266 để kết nối với network

// Các hàm hằng được khởi tạo để dễ sử dụng
#define FIREBASE_HOST "hethongbaotrom-b4955-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "4yEge3xYbiZktDtPHpvkHqVWobj48M7U2aaLZrP3"
#define WIFI_SSID "T3.10 T3.11"
#define WIFI_PASSWORD "Tanvubuilding01"

int relay=2;//D4
int cb=4;   //D2

//Khai báo FirebaseESP8266 data object
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
  // Đọc nhiệt độ hoặc độ ẩm mất khoảng 250 mili giây!
  // Các lần đọc cảm biến 'cũ' cũng có thể  tới 2 giây (đây là một cảm biến rất chậm)
  
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

// Link với Firebase 
void firebasereconnect(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

//
void loop() {
    sensorUpdate();
    int gtcb = digitalRead(cb);
    if(gtcb==1) digitalWrite(relay,HIGH);
    else digitalWrite(relay,LOW);
    delay(100);
}