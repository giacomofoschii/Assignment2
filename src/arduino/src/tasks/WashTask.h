#ifndef _WASH_TASK__
#define _WASH_TASK__

#include "Task.h"
#include "model/CarWasher.h"
#include "devices/TempSensorImpl.h"
#include "BlinkTask.h"

class WashTask: public Task {
  private:
    CarWasher* pCarWasher;
    BlinkTask* pBlinkTask;

    void stopWashing();
    void startWashing();
    void updateWashingTime();
    enum State {WASHING, MAINTENANCE, WAITING,TEMP_IS_HIGH} state;

    long washingTime;
    long washingTimeElapsed;
    long highTempTime;

public:
    WashTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask);
    void tick();    
};

#endif