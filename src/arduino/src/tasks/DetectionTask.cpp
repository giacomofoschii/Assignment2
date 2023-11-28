#include "DetectionTask.h"
#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher,BlinkTask* pBlinkTask) : pCarWasher(pCarWasher), pBlinkTask(pBlinkTask) {
  this->pCarWasher = pCarWasher;
  this->pBlinkTask = pBlinkTask;
}

void DetectionTask::tick(){
pCarWasher->detectedPresence();

if(pCarWasher->detectedPresence() && pCarWasher->isSleeping()){
  pCarWasher->turnLightOn(LED_1);
  pCarWasher->setCheck_in();
  /*lcd message*/
}

if(pCarWasher->getTime() > 1000 && pCarWasher->isCheck_in()){
    pCarWasher->setEntering();
    pBlinkTask->setActive(true);
    }
}
