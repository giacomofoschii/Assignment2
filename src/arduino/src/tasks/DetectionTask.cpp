#include "DetectionTask.h"
#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher) : pCarWasher(pCarWasher) {
  this->pCarWasher = pCarWasher;
}

void DetectionTask::tick(){
pCarWasher->detectedPresence();

if(pCarWasher->detectedPresence() && pCarWasher->isSleeping()){
  pCarWasher->setCheck_in();
  /*lcd message*/
}

if(pCarWasher->getTime() > 1000 && pCarWasher->isCheck_in()){
    pCarWasher->setEntering();
    }
}
