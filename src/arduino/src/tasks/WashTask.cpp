#include "WashTask.h"

WashTask::WashTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask, SerialCommunication* pSerialCommunication): 
        pCarWasher(pCarWasher), pBlinkTask(pBlinkTask),pSerialCommunication(pSerialCommunication) {
    state = WAITING;
}
  
void WashTask::tick(){
    switch(state) {
        case WAITING:
            if (pCarWasher->isReady() && pCarWasher->isButtonPressed()) {
                startWashing();
            }
            break;
        case WASHING:
            updateWashingTime();
            pCarWasher->setWashing();
            pBlinkTask->setPeriod(BLINK_INT2);
            pBlinkTask->setActive(true);
            pCarWasher->getCurrentTemp();

            if (washingTimeElapsed > N3) {
                pBlinkTask->setActive(false);
                pCarWasher->setFinished();
                state = WAITING;
            } else if (pCarWasher->getCurrentTemp() > MAXTEMP) {
                highTempTime = millis();
                state = TEMP_IS_HIGH;
            }
            break;
    
        case TEMP_IS_HIGH:
            updateWashingTime();
            pCarWasher->getCurrentTemp();
            if (washingTimeElapsed > N3) {
                pBlinkTask->setActive(false);
                pCarWasher->setFinished();
                state = WAITING;
            } else if (pCarWasher->getCurrentTemp() <= MAXTEMP) {
                state = WASHING;
            } else if ((millis() - highTempTime) >= N5) {
                state = MAINTENANCE;
                pCarWasher->setError();
                maintenanceTime = millis();
            }
            break;
        
        case MAINTENANCE:
            if(pSerialCommunication->isMsgAvailable()){
                String msg = pSerialCommunication->getMsg();
                if(msg == "Maintenance done"){
                    state = WASHING;
                    maintenanceTimeElapsed = millis() - maintenanceTime;
                    washingTimeElapsed -= maintenanceTimeElapsed;
                }
            }
            break;
    }
}

void WashTask::updateWashingTime() {
    long curr = millis();
    washingTimeElapsed += curr - washingTime ;
    washingTime = curr;
    long remaining = remainingTime();
    pCarWasher->LCDcountdown(remaining);
}

void WashTask::startWashing() {
    washingTime = millis();
    washingTimeElapsed = 0;
    maintenanceTime = 0;
    state = WASHING;
}

long WashTask::remainingTime() {
    return N3 - washingTimeElapsed;
}