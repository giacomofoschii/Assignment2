#include "SerialCommunication.h"

#include "config.h"

CarWasher* SerialCommunication::pCarWasher; // Aggiunta il tipo della classe davanti a pCarWasher

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
            msg = "WAITING_FOR_CAR";
            break;
        case CHECK_IN:
            msg = "CAR_DETECTED_FOR_CHECK_IN";
            break;
        // ... Altri casi
        default:
            msg = "";   
    }
    return msg;
}
