#ifndef NodeDNS_h
#define NodeDNS_h

#include <ESP8266mDNS.h>

class NodeDNS
{
  public: 
    NodeDNS(const char* dns_name);
    void begin();
  private:
    const char* _dns_name;
};

#endif
