#include <ESP8266mDNS.h>
#include "NodeDNS.h"
#define DEBUG 1

NodeDNS::NodeDNS(const char* dns_name){
  _dns_name = dns_name;
  #ifdef DEBUG
      Serial.begin(115200);
  #endif
}

void NodeDNS::begin(){
  #ifdef DEBUG
    if (MDNS.begin(_dns_name)) 
    {              
      Serial.println("mDNS responder started on " + String(_dns_name) + ".local");
    } else {
      Serial.println("Error setting up MDNS responder!");
    }
  #endif
}
