#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

#include "model/CarWasher.h" 
#include "config.h"

class SerialCommunication {
public:
    SerialCommunication(CarWasher* pcw);
    void init();
    void update();
    bool isMsgAvailable();
    String getMsg();
    

private:
    static CarWasher* pCarWasher;
    String stateAsString(State currentState);
};

#endif
