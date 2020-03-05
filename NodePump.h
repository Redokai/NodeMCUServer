#ifndef NodePump_h
#define NodePump_h

#include "Arduino.h"

class NodePump
{
  public: 
    NodePump(int relayId);
    void Activate();
    void Deactivate();
    void SetRelayId(int relay_id);
    int GetState();
  private:
    int _state;
    int _relay_id;
};

#endif
