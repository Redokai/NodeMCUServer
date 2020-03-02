#ifndef NodeServer_h
#define NodeServer_h

#include "Arduino.h"
#include <ESP8266WebServer.h>

class NodeServer
{
  public: 
    NodeServer();
    NodeServer(int port);
    void begin();
    void handleClient();
  private:
    bool _flag;
    friend void handleRoot();
    friend void handleSwitchFlag();
};

#endif
