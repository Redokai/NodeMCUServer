#include "Arduino.h"
#include "NodePump.h"
#define DEBUG 1

NodePump::NodePump(int relayId){
  _relay_id = relayId;
  pinMode(_relay_id, OUTPUT);
  #ifdef DEBUG
      Serial.begin(115200);
  #endif
}

void NodePump::Activate(){
  _state = HIGH;
  digitalWrite(_relay_id, _state);
  #ifdef DEBUG
//    Serial.println("Pump " + String(_relay_id) + " switched on");
  #endif
}

void NodePump::Deactivate(){
  _state = LOW;
  digitalWrite(_relay_id, _state);
  #ifdef DEBUG
//    Serial.println("Pump " + String(_relay_id) + " switched off");
  #endif
}

int NodePump::GetState(){
  return _state;
}

void NodePump::SetRelayId(int relay_id){
  _relay_id = relay_id;
  pinMode(_relay_id, OUTPUT);
}
