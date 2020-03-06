#include "Arduino.h"
#include <ESP8266WebServer.h>
#include "NodeServer.h"
#define DEBUG 1

int _port=80;
bool _flag=false;

void handleRoot();
void handleSwitchFlag();

ESP8266WebServer _server(_port);

NodeServer::NodeServer(){
  #ifdef DEBUG
      Serial.begin(115200);
  #endif
}

NodeServer::NodeServer(int port){
  _port = port;
  ESP8266WebServer _server(_port);
  #ifdef DEBUG
      Serial.begin(115200);
  #endif
}

void NodeServer::begin(){
  _server.on("/", HTTP_GET, handleRoot);
  _server.on("/switch", HTTP_GET, handleSwitchFlag);
  _server.begin();
  #ifdef DEBUG
    Serial.println("HTTP server started");
  #endif
}

void handleRoot() {
//  _server.send(200, "text/html", (String)"Flag :" + String(_flag));
}

void handleSwitchFlag(){
  _flag = !_flag;
//  _server.send(200, "text/html", (String)"Flag switched to:" + String(_flag));
}

void NodeServer::handleClient(){
  _server.handleClient();
}
