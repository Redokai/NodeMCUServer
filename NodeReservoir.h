#ifndef NodeReservoir_h
#define NodeReservoir_h

#include "Arduino.h"
#include "NodePump.h"

class NodeReservoir
{
  public: 
    NodeReservoir(char* reservoir_name);
    void SetReservoirLevelSensor(int sensor_id_trigger, int sensor_id_echo);
    void ReadReservoirLevel();
    void SetPump(int relay_id);
    void ActivatePumps();
    void DeactivatePumps();
    void SendReservoirLevelWarning();
    int GetPumpState();
    char* GetName();
  private:
    long _water_level;
    long _minimum_water_level;
    int _sensor_id_trigger;
    int _sensor_id_echo;
    char* _reservoir_name;
    int _reservoir_height;
};

#endif
