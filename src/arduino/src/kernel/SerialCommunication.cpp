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
    while (Serial.available() > 0) {
        char c = Serial.read();  // Ottieni un byte dal buffer seriale
        msg += c; 
        // Potrebbe essere preferibile utilizzare una condizione basata sul tempo o verificare il terminatore di linea ('\n')
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
