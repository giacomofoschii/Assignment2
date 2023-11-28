#include "WashTask.h";

#include "config.h"

WashTask::WashTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask, SerialMonitor* pSerialMonitor): 
        pCarWasher(pCarWasher), pBlinkTask(pBlinkTask),pSerialMonitor(pSerialMonitor) {
    state = WAITING;
}
  
void WashTask::tick(){
    switch(state) {
        case WAITING:
            if (pCarWasher->isReady() && pCarWasher->isButtonPressed()) {
                startWashing();
                washingTimeElapsed = 0;
                pCarWasher->setWashing();
                pBlinkTask->setPeriod(BLINK_INT2);
                pBlinkTask->setActive(true);
            }
            break;
        case WASHING:
            updateWashingTime();
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemp() >= MAXTEMP) {
                state = TEMP_IS_HIGH;
                highTempTime = millis();
            }
            if (washingTimeElapsed >= N3) {
                state = WAITING;
                pCarWasher->setCheck_out();
                pBlinkTask->setActive(false);
            }
            break;
    
        case TEMP_IS_HIGH:
            updateWashingTime();
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemp() < MAXTEMP) {
                state = WASHING;
            }
            else if ((millis() - highTempTime) >= N4) {
                state = MAINTENANCE;
                pCarWasher->set();
            }
            break;
        
        case MAINTENANCE:
            if(pSerialMonitor->isMsgAvailable()){
                String msg = pSerialMonitor->getMsg();
                if(msg == "Maintenence done"){
                    pCarWasher->setWashing();
                    startWashing();
                }
            }
            break;
    }
}

void WashTask::updateWashingTime() {
    long curr = millis();
    washingTimeElapsed += (washingTime - curr);
    washingTime = curr;
}

void WashTask::startWashing() {
    state = WASHING;
    washingTime = millis();
}