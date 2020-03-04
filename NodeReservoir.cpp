#include "Arduino.h"
#include "NodeReservoir.h"
//#include "NodePump.h"
#define DEBUG 1

const int _DEFAULT_RESERVOIR_HEIGHT = 150;
int _DEFAULT_PUMP_RELAY = 5;

NodePump _pump(_DEFAULT_PUMP_RELAY);

NodeReservoir::NodeReservoir(char* reservoir_name){
  _reservoir_name = reservoir_name;
  _reservoir_height = _DEFAULT_RESERVOIR_HEIGHT;
  #ifdef DEBUG
      Serial.begin(115200);
  #endif
}

void NodeReservoir::SetReservoirLevelSensor(int sensor_id_trigger, int sensor_id_echo){
  _sensor_id_trigger = sensor_id_trigger;
  _sensor_id_echo = sensor_id_echo;
  pinMode(_sensor_id_trigger, OUTPUT);
  pinMode(_sensor_id_echo, INPUT);
  #ifdef DEBUG
    Serial.println("Sensor id set on reservoir " + String(_reservoir_name));
  #endif
}

void NodeReservoir::ReadReservoirLevel(){
  if(_sensor_id_trigger != NULL && _sensor_id_echo != NULL){
    long duration, mm, startTime;
    startTime = millis();
    digitalWrite(_sensor_id_trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(_sensor_id_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_sensor_id_trigger, LOW);
    duration = pulseIn(_sensor_id_echo, HIGH);
    mm = duration * 10 / 29 / 2;
    _water_level = _reservoir_height - mm;
    #ifdef DEBUG
      Serial.println("Reservoir level on " + String(_reservoir_name) + " is " + String(_water_level));
    #endif
  }
}

void NodeReservoir::SetPump(int relay_id){
  NodePump _pump(relay_id);
}

void NodeReservoir::ActivatePumps(){
  _pump.Activate();
}

void NodeReservoir::DeactivatePumps(){
  _pump.Deactivate();
}

void NodeReservoir::SendReservoirLevelWarning(){
  if(_water_level <= _minimum_water_level){
//    TODO SEND TELEMETRY;
  }
}

char* NodeReservoir::GetName(){
  return _reservoir_name;
}

int NodeReservoir::GetPumpState(){
  return _pump.GetState();
}
