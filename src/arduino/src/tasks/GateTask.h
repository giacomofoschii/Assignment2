#ifndef _GATE_TASK
#define _GATE_TASK

#define OPEN_POS 180
#define CLOSE_POS 0

#include "Task.h"
#include "config.h"
#include "model/CarWasher.h"
#include "BlinkTask.h"
#include "devices/ServoMotorImpl.h"
#include "tasks/BlinkTask.h"

class GateTask : public Task {
public:
    GateTask(CarWasher* pCarWasher);

    void tick() override;

private:
    CarWasher* pCarWasher;  
    BlinkTask* pBlinkTask;
    long startTime;
    ServoMotor* pMotor;
    enum State { OPEN, CLOSE, WAITING} state;
    
private:
    bool checkTimeElapsed(long temp);
    void openGate();
    void closeGate();
    void setState(State state);
    long elapsedTime();
};

#endif