#include "NodeServer.h"
#include "NodeWifi.h"
#include "NodeDNS.h"
#include "NodePump.h"
#include "NodeReservoir.h"
#include "NodeGarden.h"

const char* ssid     = "AssociacaoDosNinjas";
const char* password = "jijiyuki";
const char* my_dns = "rednode";
char* garden_1_name = "Tomato Garden";
char* garden_2_name = "Chery tomato Garden";

#define DEBUG 1

NodeWifi nodeWifi(ssid, password);
NodeServer nodeServer;
NodeDNS nodeDns(my_dns);
NodeGarden garden_1(garden_1_name);
NodeGarden garden_2(garden_2_name);

void setup() {

  nodeWifi.Connect();
  nodeWifi.WaitUntilConnect();

  nodeDns.begin();
  nodeServer.begin();

  garden_1.SetReservoirPumpRelay(LED_BUILTIN);
}

void loop(){
  nodeServer.handleClient();
  garden_1.handle();
  delay(500);
}
