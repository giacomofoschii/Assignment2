#include "DetectionTask.h"

#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher){
  this->pCarWasher = pCarWasher;
}

void DetectionTask::tick(){
pCarWasher->detectedPresence();

if(pCarWasher->detectedPresence() && pCarWasher->isSleeping()){
  pCarWasher->setCheck_in();
}
}
