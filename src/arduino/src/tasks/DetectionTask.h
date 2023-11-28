#ifndef _DETECTION_TASK__
#define _DETECTION_TASK__

#include "Task.h"
#include "devices/Pir.h"
#include "model/CarWasher.h"
#include "tasks/BlinkTask.h"

class DetectionTask: public Task {
  private:
    Pir* pir;
    CarWasher* pCarWasher;
    BlinkTask* pBlinkTask;

public:
    DetectionTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask);
    void tick();
};

#endif