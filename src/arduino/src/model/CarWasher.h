#ifndef __CARWASHER__
#define __CARWASHER__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/TempSensorLM35.h"
#include "devices/ServoMotor.h"
#include "devices/Button.h"

class CarWasher {

    public: 
        CarWasher();
        void init();

        double getCurrentTemp();
        double getCurrentDistance();

        bool isLightOn(int pin);
        bool detectedPresence();

        void turnLightOn(int pin);
        void turnLightOff(int pin);

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

    private:

        double temp;
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
        ServoMotor *servoMotor;

        enum { SLEEPING, CHECK_IN, ENTERING, READY, WASHING, ERROR, FINISHED, CHECK_OUT} state;
};


#endif