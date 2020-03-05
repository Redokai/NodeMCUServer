#include "Arduino.h"
#include "NodeGarden.h"
#include "NodeReservoir.h"
#define DEBUG 1

const long _DEFAULT_CYCLE_TIME = 15 * 60000;
const long _DEFAULT_WATERING_TIME = 2 * 60000;
char* _DEFAULT_GARDEN_NAME = "Garden 1";

NodeReservoir _reservoir(_DEFAULT_GARDEN_NAME);

NodeGarden::NodeGarden(char* garden_name){
_garden_name = garden_name;
_cycle_time = _DEFAULT_CYCLE_TIME;
_watering_time = _DEFAULT_WATERING_TIME;
_last_cycle_starttime = millis();
SetReservoirName( strcat(garden_name, " reservoir"));
#ifdef DEBUG
    Serial.begin(115200);
    Serial.println("Garden " + String(_garden_name) + " started ");
#endif
}

void NodeGarden::SetReservoirName(char* reservoir_name){
  NodeReservoir _reservoir(reservoir_name);
  #ifdef DEBUG
  //    Serial.println("Reservoir " + String(_reservoir.GetName()) + " added to " + _garden_name);
  #endif
}
  
void NodeGarden::handle(){
  long now = millis();
  
  if((_last_cycle_starttime + _watering_time > now) && (_reservoir.GetPumpState() == LOW)){
    _reservoir.ActivatePumps();
    _last_cycle_starttime = now;
  }
  else if(_last_cycle_starttime + _watering_time < now && _reservoir.GetPumpState() == HIGH){
    _reservoir.DeactivatePumps();
  }
  else if(_last_cycle_starttime + _cycle_time < now && _reservoir.GetPumpState() == LOW){
    _reservoir.ActivatePumps();
    _last_cycle_starttime = now;
  };
}

void NodeGarden::SetReservoirPumpRelay(int relay_id){
  _reservoir.SetPump(relay_id);
  #ifdef DEBUG
      Serial.println("Reservoir pump relay set to " + String(relay_id) + " in " + _garden_name);
  #endif
}

void NodeGarden::SetReservoirLevelSensor(int sensor_id_trigger, int sensor_id_echo){
  _reservoir.SetReservoirLevelSensor(sensor_id_trigger, sensor_id_echo);
}

void NodeGarden::SetCycleInterval(long cycle_interval){
  _cycle_time = cycle_interval;
}

void NodeGarden::SetWateringInterval(long watering_interval){
  _watering_time = watering_interval;
}
