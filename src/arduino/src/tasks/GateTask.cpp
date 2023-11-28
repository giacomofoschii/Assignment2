#include "GateTask.h"
#include "config.h"
#include "model/CarWasher.h"
#include "devices/ServoMotorImpl.h"
#include "BlinkTask.h"


GateTask::GateTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask) : pCarWasher(pCarWasher), pBlinkTask(pBlinkTask) {
}

void GateTask::tick(){
    if(pCarWasher->isEntering()){
        pBlinkTask->setActive(true);
        openGate();
    }
    else if(pCarWasher->isReady()){
        pBlinkTask->setActive(false);
        closeGate();
    }
    else if(pCarWasher->isFinished()){
        pCarWasher->turnLightOn(LED_3);
        openGate();
        pBlinkTask->setActive(false);
    }
    else if(pCarWasher->isCheck_out()){
        pCarWasher->turnLightOff(LED_3);
        closeGate();
        pCarWasher->isSleeping();
    }
    
}
