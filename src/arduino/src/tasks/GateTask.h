#ifndef _GATE_TASK
#define _GATE_TASK

#define OPEN_POS 180
#define CLOSE_POS 0

#include "Task.h"
#include "model/CarWasher.h"
#include "BlinkTask.h"

class GateTask : public Task {
public:
    GateTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask);

    void tick() override;

private:
    bool checkTimeElapsed(long temp);
    void openGate();
    bool closeGate();

private:
    CarWasher* pCarWasher;
    BlinkTask* pBlinkTask;
  
    long perfectTime;
};

#endif