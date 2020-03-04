#include "NodeServer.h"
#include "NodeWifi.h"
#include "NodeDNS.h"
#include "NodePump.h"
#include "NodeReservoir.h"

const char* ssid     = "AssociacaoDosNinjas";
const char* password = "jijiyuki";
const char* my_dns = "rednode";

#define DEBUG 1


NodeWifi nodeWifi(ssid, password);
NodeServer nodeServer;
NodeDNS nodeDns(my_dns);
NodePump pump(1);

void setup() {

  nodeWifi.Connect();
  nodeWifi.WaitUntilConnect();

  nodeDns.begin();

  nodeServer.begin();
}

void loop(){
  nodeServer.handleClient();
}
