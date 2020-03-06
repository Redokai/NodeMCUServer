#include "Arduino.h"
#include "NodeWifi.h"
#include <ESP8266WiFi.h>

#define DEBUG 1

NodeWifi::NodeWifi(const char* ssid,const char* password){
  _ssid = ssid;
  _password = password;
  #ifdef DEBUG
      Serial.begin(115200);
  #endif
}

void NodeWifi::Connect(){
  WiFi.begin(_ssid, _password);
  #ifdef DEBUG
//      Serial.println("Connection to (INSIDE) " + String(_ssid));
  #endif
}

void NodeWifi::WaitUntilConnect(){
  int i=0;
  while (WiFi.status() != WL_CONNECTED){
    delay(200);
    #ifdef DEBUG
      Serial.println("Not connected (" + String(i++) + ")");
    #endif
  }
  #ifdef DEBUG
//      Serial.println("Successfully connected to " + String(_ssid) + " - " + String(WiFi.localIP()));
  #endif
}
