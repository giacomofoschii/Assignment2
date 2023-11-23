#include "DetectionTask.h"

#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher): pCarWasher(pCarWasher){
  pir = new Pir(PIR_PIN);
}

void DetectionTask::tick(){
/*if (pCarWasher->isWaitingForCarState() && pCarWasher->detectedPresence()) {
        pCarWasher->setCarDetectedForCheckInState();
    }*/}
