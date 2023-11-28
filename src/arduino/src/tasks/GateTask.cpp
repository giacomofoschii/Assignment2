#include "GateTask.h"


GateTask::GateTask(CarWasher* pCarWasher) : pCarWasher(pCarWasher) {
   state = CLOSE;
}

void GateTask::tick(){
    switch (state)
    {
    case CLOSE:
        if(pCarWasher->isEntering()){
            openGate();
            pBlinkTask->setActive(true);
        } else if (pCarWasher->isFinished()) {
            openGate();
            pBlinkTask->setActive(false);
        }
        break;
    case OPEN:
        if(pCarWasher->isReady()){
            closeGate();
            pBlinkTask->setActive(false);
        } else if (pCarWasher->isCheck_out()) {
            closeGate();
            pCarWasher->setSleeping();
        }
        break;
    }
}

void GateTask::setState(State state){
    this->state = state;
}

long GateTask::elapsedTime(){
    return millis() - startTime;
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