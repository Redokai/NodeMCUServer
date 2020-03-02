#ifndef NodeWifi_h
#define NodeWifi_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

class NodeWifi
{
  public: 
    NodeWifi(const char* ssid, const char* password);
    void WaitUntilConnect();
    void Connect();
  private:
    const char* _ssid;
    const char* _password;
};

#endif
