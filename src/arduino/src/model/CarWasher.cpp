#include "CarWasher.h"

volatile bool detectionInSleep = false;

void wake(){
    detectionInSleep = true;
    delay(100);
}

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
    lcd = new LCD();
    servoMotor->on();
    detectedPres = false;
    State state;
    this->setSleeping();
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
    lcd->clearDisplay();
    detectionInSleep = false;
    sleep();
}

void CarWasher::setCheck_in(){
    state = CHECK_IN;
    detachInterrupt(digitalPinToInterrupt(PIR_PIN));
    temp=millis();
    turnLightOn(LED_1);
    LCDwrite("Welcome!");
}

void CarWasher::setEntering(){
    state = ENTERING;
    LCDwrite("Proceed to the Washing Area");
}

void CarWasher::setReady(){
    state = READY;
    LCDwrite("Ready to Wash");
}

void CarWasher::setWashing(){
    state = WASHING;
}

void CarWasher::setError(){
    state = ERROR;
    LCDwrite("Detected a Problem - Please Wait");
}

void CarWasher::setFinished(){
    state = FINISHED;
    turnLightOn(LED_3);
    turnLightOff(LED_2);
    LCDwrite("Washing complete, you can leave the area");
}

void CarWasher::setCheck_out(){
    state = CHECK_OUT;
    turnLightOff(LED_3);
    delay(1500);
    setSleeping();
}

State CarWasher::getState() {
    return state;
}

double CarWasher::getCurrentTemp(){
    return tempSensor->getTemperature();
}

double CarWasher::getCurrentDistance(){
    return this->sonar->getDistance();
}

long CarWasher::getCurrentTime(){
    return time;
}

long CarWasher::getElapsedTime() {
    return millis() - time;
}

bool CarWasher::detectedPresence(){
    this->pir->sync();
    return pir->isDetected();
}

bool CarWasher::isButtonPressed(){
    button->sync();
    return button->isPressed();
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

void CarWasher::LCDwrite(String msg){
    lcd->clearDisplay();
    lcd->setCursorDisplay(0, 0);
    lcd->printText(msg);
}

void CarWasher::LCDcountdown(long remainingTime){
    lcd->clearDisplay();
    lcd->setCursorDisplay(0, 0);
    lcd->printText("Time left: " + String(remainingTime/1000) + "s");
}

void CarWasher::ServoMotorOn(){
    servoMotor->on();
}

void CarWasher::ServoMotorOff(){
    servoMotor->off();
}

void CarWasher::MotorPosition(int position){
    servoMotor->setPosition(position);
}

void CarWasher::sleep(){
    lcd->printText("No one around");
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), wake, RISING); 
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_enable();
    sleep_mode();  
    sleep_disable();  
}