#include "Arduino.h"
#include "NodeGarden.h"
#include "NodeReservoir.h"
#include "AdafruitIO_WiFi.h"
#define DEBUG 1

const long _DEFAULT_CYCLE_TIME = 15 * 60000;
const long _DEFAULT_WATERING_TIME = 2 * 60000;
char* _DEFAULT_GARDEN_NAME = "Garden 1";

#define IO_ACTION_FEED         "action-tracking"
#define IO_DEVICE_FEED         "device-tracking"

//NodeReservoir _reservoir(_DEFAULT_GARDEN_NAME);
AdafruitIO_WiFi *_io;
AdafruitIO_Feed *_action_logger;
AdafruitIO_Feed *_device_logger;

NodeGarden::NodeGarden(char* garden_name, AdafruitIO_WiFi *io){
_garden_name = garden_name;
_cycle_time = _DEFAULT_CYCLE_TIME;
_watering_time = _DEFAULT_WATERING_TIME;
_last_cycle_starttime = millis();
_io = io;
_action_logger = _io->feed(IO_ACTION_FEED);
_device_logger = _io->feed(IO_DEVICE_FEED);
_reservoir = new NodeReservoir(_DEFAULT_GARDEN_NAME);
#ifdef DEBUG
    Serial.begin(115200);
    Serial.println("Garden " + String(_garden_name) + " started ");
#endif
}

void NodeGarden::SetReservoirName(char* reservoir_name){
  _reservoir->SetName(reservoir_name);
  #ifdef DEBUG
      Serial.println("Reservoir " + String(_reservoir->GetName()) + " added to " + _garden_name);
  #endif
}
  
void NodeGarden::handle(){
  long now = millis();
  
  if((_last_cycle_starttime + _watering_time > now) && (_reservoir->GetPumpState() == LOW)){
    _reservoir->ActivatePumps();
    _last_cycle_starttime = now;
    _action_logger->save(String("Pump activated on ") + String(_garden_name));
    _pump_state_logger->save(0);
  }
  else if(_last_cycle_starttime + _watering_time < now && _reservoir->GetPumpState() == HIGH){
    _reservoir->DeactivatePumps();
    _action_logger->save(String("Pump deactivated on ") + String(_garden_name));
    _pump_state_logger->save(100);
  }
  else if(_last_cycle_starttime + _cycle_time < now && _reservoir->GetPumpState() == LOW){
    _reservoir->ActivatePumps();
    _last_cycle_starttime = now;
    _action_logger->save(String("Pump activated on ") + String(_garden_name));
    _pump_state_logger->save(0);
  };
}

void NodeGarden::SetReservoirPumpRelay(int relay_id){
  _reservoir->SetPump(relay_id);
  #ifdef DEBUG
      Serial.println("Reservoir pump relay set to " + String(relay_id) + " in " + _garden_name);
  #endif
}

void NodeGarden::SetReservoirLevelSensor(int sensor_id_trigger, int sensor_id_echo){
  _reservoir->SetReservoirLevelSensor(sensor_id_trigger, sensor_id_echo);
}

void NodeGarden::SetCycleInterval(long cycle_interval){
  _cycle_time = cycle_interval;
}

void NodeGarden::SetWateringInterval(long watering_interval){
  _watering_time = watering_interval;
}

void NodeGarden::SetPumpStatusFeed(char* feed){
  _pump_status_feed = feed;
  _pump_state_logger = _io->feed(_pump_status_feed);
}
