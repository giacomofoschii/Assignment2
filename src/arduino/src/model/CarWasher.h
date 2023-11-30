#ifndef __CARWASHER__
#define __CARWASHER__

#include <Arduino.h>
#include "config.h"
#include "devices/ButtonImpl.h"
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/ServoMotorImpl.h"
#include "devices/TempSensorLM35.h"
#include "devices/LCD.h"
#include <avr/sleep.h>

class CarWasher {

    public: 
        CarWasher();
        void init();

        bool isSleeping();
        bool isCheck_in();
        bool isEntering();
        bool isReady();
        bool isWashing();
        bool isError();
        bool isFinished();
        bool isCheck_out();

        void setSleeping();
        void setCheck_in();
        void setEntering();
        void setReady();
        void setWashing();
        void setError();
        void setFinished();
        void setCheck_out();

        State getState();

        double getCurrentTemp();
        double getCurrentDistance();
        long getCurrentTime();
        long getElapsedTime();

        bool detectedPresence();
        bool isButtonPressed();

        bool isLightOn(int pin);
        void turnLightOn(int pin);
        void turnLightOff(int pin);

        void LCDwrite(String text);
        void LCDcountdown(long remainingTime);

        void ServoMotorOn();
        void ServoMotorOff();
        void MotorPosition(int position);

        void sleep();

    private:

        double temp;
        long time;
        double distance;
        bool detectedPres;
        bool led01On;
        bool led02On;
        bool led03On;
       
    
        Button* button;
        Led* led01;
        Led* led02;
        Led* led03;
        Pir* pir;
        Sonar* sonar;
        TempSensorLM35* tempSensor;
        ServoMotor* servoMotor;
        LCD* lcd;
        State state;
};


#endif