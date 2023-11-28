#include "WashTask.h";

#include "config.h"

WashTask::WashTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask, SerialCommunication* pSerialCommunication): 
        pCarWasher(pCarWasher), pBlinkTask(pBlinkTask),pSerialCommunication(pSerialCommunication) {
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
            pCarWasher->getCurrentTemp();
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
            pCarWasher->getCurrentTemp();
            if (pCarWasher->getCurrentTemp() < MAXTEMP) {
                state = WASHING;
            }
            else if ((millis() - highTempTime) >= N4) {
                state = MAINTENANCE;
                pCarWasher->setError();
            }
            break;
        
        case MAINTENANCE:
            if(pSerialCommunication->isMsgAvailable()){
                String msg = pSerialCommunication->getMsg();
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