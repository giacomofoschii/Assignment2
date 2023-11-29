#include "DetectionTask.h"
#include "config.h"

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
      if(pCarWasher->isCheck_in()){
        state = DETECTING;
        timer = millis();
      }
      break;
  }
}
