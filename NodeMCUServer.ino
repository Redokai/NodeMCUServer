#include "NodeServer.h"
//#include "NodeWifi.h"
#include "NodeDNS.h"
#include "NodePump.h"
#include "NodeReservoir.h"
#include "NodeGarden.h"
#include "AdafruitIO_WiFi.h"

const char* ssid     = "AssociacaoDosNinjas";
const char* password = "jijiyuki";
const char* my_dns = "rednode";
char* garden_1_name = "Tomato Garden";
char* garden_2_name = "Chery tomato Garden";

#define DEBUG 1
#define WIFI_SSID     "AssociacaoDosNinjas"
#define WIFI_PASS     "jijiyuki"
#define IO_USERNAME   "redokai"
#define IO_KEY        "aio_ZbxD30WjjpTii9rdYiaYTd3LeKCy"
#define IO_FEED       "Action Tracking"

//NodeWifi nodeWifi(ssid, password);
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *feed = io.feed(IO_FEED);

NodeServer nodeServer;
NodeDNS nodeDns(my_dns);
NodeGarden garden_1(garden_1_name);
NodeGarden garden_2(garden_2_name);

void setup() {

//  nodeWifi.Connect();
//  nodeWifi.WaitUntilConnect();

  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  nodeDns.begin();
  nodeServer.begin();

  garden_1.SetReservoirPumpRelay(LED_BUILTIN);

  
}

void loop(){
  nodeServer.handleClient();
  garden_1.handle();
  io.run();
  feed->save('try');
  delay(1000);
}
