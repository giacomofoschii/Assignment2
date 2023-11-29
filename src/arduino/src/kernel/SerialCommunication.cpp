#include "SerialCommunication.h"

#include "config.h"

CarWasher* SerialCommunication::pCarWasher;

SerialCommunication::SerialCommunication(CarWasher* pcw) {
    pCarWasher = pcw; 
}

void SerialCommunication::init() {
    Serial.begin(9600);
}

void SerialCommunication::update() {
    pCarWasher->getCurrentTemp();
    String msg = stateAsString(pCarWasher->getState()) + ":" + pCarWasher->getCurrentTemp();
    Serial.println(msg);
}

bool SerialCommunication::isMsgAvailable() {
    return Serial.available() > 0;
}
    
String SerialCommunication::getMsg() {
    String msg = "";
    char c;
  
    while (Serial.available() > 0 && (c = Serial.read()) != '\n') {
        msg += c;
    }
  
    return msg;
}


String SerialCommunication::stateAsString(State currentState) {
    String msg;
    switch(currentState) {
        case SLEEPING:
            msg = "SLEEPING";
            break;
        case CHECK_IN:
            msg = "CHECK_IN";
            break;
        case ENTERING:
            msg = "ENTERING";
            break;
        case READY:
            msg = "READY";
            break;
        case WASHING:
            msg = "WASHING";
            break;
        case ERROR:
            msg = "ERROR";
            break;
        case FINISHED:
            msg = "FINISHED";
            break;
        case CHECK_OUT:
            msg = "CHECK_OUT";
            break;
        default:
            msg = "";
    }
    return msg;
}
