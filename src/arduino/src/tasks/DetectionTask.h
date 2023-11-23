#ifndef _DETECTION_TASK__
#define _DETECTION_TASK__

#include "Task.h"
#include "devices/Pir.h"
#include "model/CarWasher.h"

class DetectionTask: public Task {
  private:
    Pir* pir;
    CarWasher* pCarWasher;

public:
    DetectionTask(CarWasher* pCarWasher);
    void tick();
};

#endif