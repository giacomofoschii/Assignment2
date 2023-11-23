#ifndef __CARWASHER__
#define __CARWASHER__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/TempSensorLM35.h"
#include "devices/ServoMotor.h"

class CarWasher {

    public: 
        CarWasher();
        void init();

        double getCurrentTemp();

        bool isLightOn();
        bool detectedPresence();

        void turnLightOn();
        void turnLightOff();

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
        bool detectedPres;

        enum { SLEEPING, CHECK_IN, ENTERING, READY, WASHING, ERROR, FINISHED, CHECK_OUT} state;
};


#endif