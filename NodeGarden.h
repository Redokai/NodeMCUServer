#ifndef NodeGarden_h
#define NodeGarden_h

#include "Arduino.h"
#include "NodeReservoir.h"
#include "AdafruitIO_WiFi.h"

class NodeGarden
{
  public: 
    NodeGarden(char* garden_name, AdafruitIO_WiFi *io);
    void handle();
    void SetReservoirName(char* reservoir_name);
    void SetReservoirPumpRelay(int relay_id);
    void SetReservoirLevelSensor(int sensor_id_trigger, int sensor_id_echo);
    void SetCycleInterval(long cycle_interval);
    void SetWateringInterval(long watering_interval);
    void SetPumpStatusFeed(char* feed);
  private:
    char* _garden_name;
    unsigned long _last_cycle_starttime;
    long _cycle_time;
    long _watering_time;
    char* _pump_status_feed;
    NodeReservoir *_reservoir;
    AdafruitIO_Feed *_pump_state_logger;
};

#endif
