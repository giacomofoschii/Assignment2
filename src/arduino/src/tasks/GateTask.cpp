#include "GateTask.h"


GateTask::GateTask(CarWasher* pCarWasher) : pCarWasher(pCarWasher) {
   pMotor = new ServoMotorImpl(GATE_PIN);
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
    pMotor->on();
    pMotor->setPosition(OPEN_POS);
    setState(OPEN);
}

void GateTask::closeGate(){
    pMotor->setPosition(CLOSE_POS);
    pMotor->off();
    setState(CLOSE);
}