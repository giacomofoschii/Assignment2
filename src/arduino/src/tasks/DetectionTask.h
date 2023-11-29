#ifndef _DETECTION_TASK__
#define _DETECTION_TASK__

#include "Task.h"
#include "devices/Pir.h"
#include "model/CarWasher.h"

class DetectionTask: public Task {
  private:
    long timer;
    Pir* pir;
    CarWasher* pCarWasher;
    enum state {DETECTING, SLEEPING} state;

public:
    DetectionTask(CarWasher* pCarWasher);
    void tick();
};

#endif