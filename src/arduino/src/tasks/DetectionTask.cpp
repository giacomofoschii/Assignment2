#include "DetectionTask.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher) : pCarWasher(pCarWasher) {
  this->pCarWasher = pCarWasher;
}

void DetectionTask::tick(){
  switch(state) {
    case DETECTING:
      if(millis() - timer >= N1){
          pCarWasher->setEntering();
          state = SLEEPING;
        }
      break;
    case SLEEPING:
      if(pCarWasher->isSleeping() && pCarWasher->detectedPresence()){
        state = DETECTING;
        timer = millis();
        pCarWasher->setCheck_in();
      }
      break;
  }
}
