#include "NodeServer.h"
#include "NodeDNS.h"
#include "NodeGarden.h"
#include "AdafruitIO_WiFi.h"

#define DEBUG 1
#define WIFI_SSID       "AssociacaoDosNinjas"
#define WIFI_PASS       "jijiyuki"
#define DNS             "rednode"
#define GARDEN1_NAME    "Tomato Garden"
#define GARDEN2_NAME    "Chery tomato Garden"
#define IO_USERNAME     "redokai"
#define IO_KEY          ""
#define IO_DEVICE_FEED  "device-tracking"
#define IO_PUMP_1_FEED  "pump1-state"
#define IO_PUMP_2_FEED  "pump2-state"

const long _SHORT_CYCLE_TIME = 5 * 60000;
const long _SHORT_WATERING_TIME = 1 * 60000;

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *logger = io.feed(IO_DEVICE_FEED);

NodeServer nodeServer;
NodeDNS nodeDns(DNS);
NodeGarden garden_1(GARDEN1_NAME, &io);
NodeGarden garden_2(GARDEN2_NAME, &io);

void setup() {

  AdafruitConnect();

  nodeDns.begin();
  nodeServer.begin();

  garden_1.SetReservoirPumpRelay(2);
  garden_1.SetPumpStatusFeed(IO_PUMP_1_FEED);

  garden_2.SetReservoirPumpRelay(16);
  garden_2.SetPumpStatusFeed(IO_PUMP_2_FEED);
  garden_2.SetWateringInterval(_SHORT_WATERING_TIME);
  garden_2.SetCycleInterval(_SHORT_CYCLE_TIME);

}

void loop(){
  nodeServer.handleClient();
  garden_1.handle();
  delay(200);
  garden_2.handle();
  io.run();
}

void AdafruitConnect(){
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    delay(500);
  }
  logger->save("Garden Manager Innitialization ...");
  delay(2000);
  String msg = String("Stablished connection on ") + String(WIFI_SSID);
  logger->save(msg);
  delay(2000);
}
