#include "GateTask.h"
#include "config.h"
#include "model/CarWasher.h"
#include "devices/ServoMotorImpl.h"


GateTask::GateTask(CarWasher* pCarWasher) : pCarWasher(pCarWasher) {
   pMotor = new ServoMotorImpl(GATE_PIN);
   state = CLOSE;
}

void GateTask::tick(){
    switch (state)
    {
    case CLOSE:
        if(pCarWasher->isEntering() || pCarWasher->isFinished()){
            openGate();
        }
        break;
    case OPEN:
        if(pCarWasher->isReady()){
            closeGate();
        }
        break;
    }
}

void GateTask::setState(State state){
    this->state = state;
    startTime = millis();

}

long GateTask::elapsedTime(){
    return millis() - startTime;
}

void GateTask::openGate(){
    pMotor->on();
    pMotor->setPosition(OPEN_POS);
    setState(OPEN);
    if(elapsedTime() > 1000){
        pMotor->off();
    }
}

void GateTask::closeGate(){
    pMotor->on();
    pMotor->setPosition(CLOSE_POS);
    setState(CLOSE);
    if(elapsedTime() > 1000){
        pMotor->off();
    }
}