#include "DetectionTask.h"
#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher) : pCarWasher(pCarWasher) {
  this->pCarWasher = pCarWasher;
}

void DetectionTask::tick(){
  switch(state) {
    case DETECTING:
      pCarWasher->detectedPresence();
      if(pCarWasher->detectedPresence() && pCarWasher->isSleeping()){
        pCarWasher->setCheck_in();
      } else if(pCarWasher->isCheck_in() && pCarWasher->getElapsedTime() >= N1){
          pCarWasher->setEntering();
          state = SLEEPING;
        }
      break;
    case SLEEPING:
      if(pCarWasher->isSleeping()){
        state = DETECTING;
      }
      break;
  }
}
