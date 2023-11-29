#include "GateTask.h"


GateTask::GateTask(CarWasher* pCarWasher, BlinkTask* pBlinkTask) : pCarWasher(pCarWasher), pBlinkTask(pBlinkTask) {
   state = CLOSE;
}

void GateTask::tick(){
    switch (state)
    {
    case CLOSE:
        if(pCarWasher->isEntering()){
            openGate();
            pBlinkTask->setPeriod(BLINK_INT1);
            pBlinkTask->setActive(true);
        } else if (pCarWasher->isFinished()) {
            openGate();
        }
        break;

    case OPEN:
        pCarWasher->getCurrentDistance();
        if((pCarWasher->isEntering() && pCarWasher->getCurrentDistance() <= MAXDIST) || (pCarWasher->isFinished() && pCarWasher->getCurrentDistance() >= MAXDIST)){
            state=WAITING;
            startTime = millis();
        }
        break;

    case WAITING:
        pCarWasher->getCurrentDistance();
        if (pCarWasher->isEntering()) {
            if (pCarWasher->getCurrentDistance() > MINDIST) {
                state = OPEN;
            }
            else if (checkTimeElapsed(N2)) {
                pBlinkTask->setActive(false);
                pCarWasher->setReady();
                closeGate();
            }
        }
        if (pCarWasher->isFinished()) {
            if (pCarWasher->getCurrentDistance() < MAXDIST) {
                state = OPEN;
            }
            else if (checkTimeElapsed(N4)) {
                closeGate();
                pCarWasher->setCheck_out();
            }
        }
        break;
    }
}

void GateTask::setState(State state){
    this->state = state;
}

bool GateTask::checkTimeElapsed(long temp) {
    return (millis() - startTime) >= temp;
}

void GateTask::openGate(){
    pCarWasher->ServoMotorOn();
    pCarWasher->MotorPosition(OPEN_POS);
    setState(OPEN);
}

void GateTask::closeGate(){
    pCarWasher->MotorPosition(CLOSE_POS);
    pCarWasher->ServoMotorOff();
    setState(CLOSE);
}