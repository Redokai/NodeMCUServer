//#include "Arduino.h"
//#include "NodeGarden.h"
//#include "NodeReservoir.h"
//#define DEBUG 1
//
//namespace Garden{
//
//  const long _DEFAULT_CYCLE_TIME = 15 * 60000;
//  const long _DEFAULT_WATERING_TIME = 2 * 60000;
//  
//  NodeGarden::NodeGarden(char* garden_name){
//  _garden_name = garden_name;
//  _cycle_time = _DEFAULT_CYCLE_TIME;
//  _watering_time = _DEFAULT_WATERING_TIME;
//  _last_cycle_starttime = millis();
//  #ifdef DEBUG
//      Serial.begin(115200);
//      Serial.println("Garden " + String(_garden_name) + " started ");
//  #endif
//  }
//  
//  void NodeGarden::addReservoir(char* reservoir_name){
//    NodeReservoir _reservoir(reservoir_name);
//    #ifdef DEBUG
//    //    Serial.println("Reservoir " + String(_reservoir.GetName()) + " added to " + _garden_name);
//    #endif
//  }
//    
//  void NodeGarden::handle(){
//    long now = millis();
//    
//    if((_last_cycle_starttime + _watering_time > now) && (_reservoir().GetPumpState() == LOW)){
//      _reservoir().ActivatePumps();
//      _last_cycle_starttime = now;
//    }
//    else if(_last_cycle_starttime + _watering_time < now && _reservoir().GetPumpState() == HIGH){
//      _reservoir().DeactivatePumps();
//    }
//    else if(_last_cycle_starttime + _cycle_time < now && _reservoir().GetPumpState() == LOW){
//      _reservoir.ActivatePumps();
//      _last_cycle_starttime = now;
//    };
//  }
//}
