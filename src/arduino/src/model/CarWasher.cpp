#include "CarWasher.h"
#include "config.h"
#include "devices/ButtonImpl.h"
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/ServoMotorImpl.h"
#include "devices/TempSensorLM35.h"

CarWasher::CarWasher() {
  // TODO Auto-generated constructor stub
}

void CarWasher::init(){
    button = new ButtonImpl(BUT_1);
    led01 = new Led(LED_1);
    led02 = new Led(LED_2);
    led03 = new Led(LED_3);
    pir = new Pir(PIR_PIN);
    sonar = new Sonar(ECHO_PIN, TRIG_PIN, MAXTIME);
    tempSensor = new TempSensorLM35(TEMP_PIN);
    servoMotor = new ServoMotorImpl(GATE_PIN);

    detectedPres = false;
    /*setWaiting();*/
}

double CarWasher::getCurrentTemp(){
    return tempSensor->getTemperature();
}

double CarWasher::getCurrentDistance(){
    return sonar->getDistance();
}

bool CarWasher::isLightOn(int pin){
    if(pin == LED_1){
        return led01On;
    }else if(pin == LED_2){
        return led02On;
    }else if(pin == LED_3){
        return led03On;
    }
    return false;
}

bool CarWasher::detectedPresence(){
    this->pir->sync();
    return pir->isDetected();
}

void CarWasher::turnLightOn(int pin){
    if(pin == LED_1){
        led01->switchOn();
        led01On = true;
    }else if(pin == LED_2){
        led02->switchOn();
        led02On = true;
    }else if(pin == LED_3){
        led03->switchOn();
        led03On = true;
    }
}

void CarWasher::turnLightOff(int pin){
    if(pin == LED_1){
        led01->switchOff();
        led01On = false;
    }else if(pin == LED_2){
        led02->switchOff();
        led02On = false;
    }else if(pin == LED_3){
        led03->switchOff();
        led03On = false;
    }
}

bool CarWasher::isSleeping(){
    return state == SLEEPING;
}

bool CarWasher::isCheck_in(){
    return state == CHECK_IN;
}

bool CarWasher::isEntering(){
    return state == ENTERING;
}

bool CarWasher::isReady(){
    return state == READY;
}

bool CarWasher::isWashing(){
    return state == WASHING;
}

bool CarWasher::isError(){
    return state == ERROR;
}

bool CarWasher::isFinished(){
    return state == FINISHED;
}

bool CarWasher::isCheck_out(){
    return state == CHECK_OUT;
}

void CarWasher::setSleeping(){
    state = SLEEPING;
    turnLightOff(LED_1);
}

void CarWasher::setCheck_in(){
    state = CHECK_IN;
    turnLightOn(LED_1);
    temp=millis();
}

void CarWasher::setEntering(){
    state = ENTERING;
}

void CarWasher::setReady(){
    state = READY;
}

void CarWasher::setWashing(){
    state = WASHING;
    temp=millis();
}

void CarWasher::setError(){
    state = ERROR;
}

void CarWasher::setFinished(){
    state = FINISHED;
    turnLightOn(LED_3);
}

void CarWasher::setCheck_out(){
    state = CHECK_OUT;
    turnLightOff(LED_3);
}

long CarWasher::getTime(){
    return time;
}
