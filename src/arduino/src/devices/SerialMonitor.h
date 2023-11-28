#ifndef _SERIAL_MONITOR__
#define _SERIAL_MONITOR__

#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

class LcdDisplay {
    
    public:
        LcdDisplay();
        void printText(String text);
        void setCursorDisplay(int x, int y);
        void clearDisplay();

    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif