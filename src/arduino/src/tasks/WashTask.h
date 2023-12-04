#ifndef _WASH_TASK__
#define _WASH_TASK__

#include "Task.h"
#include "config.h"
#include "model/CarWasher.h"
#include "devices/TempSensorImpl.h"
#include "BlinkTask.h"
#include "kernel/SerialCommunication.h"

class WashTask: public Task {
  private:
    CarWasher* pCarWasher;
    BlinkTask* pBlinkTask;
    SerialCommunication* pSerialCommunication;

    void stopWashing();
    void startWashing();
    void updateWashingTime();
    long remainingTime();
    enum State {WASHING, MAINTENANCE, WAITING,TEMP_IS_HIGH} state;

    long washingTime;
    long washingTimeElapsed;
    long highTempTime;
    long maintenanceTime;
    long maintenanceTimeElapsed;

public:
    WashTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask, SerialCommunication* pSerialCommunication);
    void tick();    
};

#endif