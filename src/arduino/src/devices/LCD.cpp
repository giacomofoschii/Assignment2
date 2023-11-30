#include "LCD.h"

LCD::LCD() {
    lcd.init();
    lcd.backlight();
} 

void LCD::printText(String text) {
    lcd.print(text);
}

void LCD::setCursorDisplay(int x, int y) {
    lcd.setCursor(x, y);
}

void LCD::clearDisplay() {
    lcd.clear();
}

void LCD::countdown(int seconds) {
    while(seconds >= 0) {
        startCurrentTime();
        if(getElapsedTime()>= 1000) {
        clearDisplay();
        printText("Time left:" + String(seconds));
        seconds--;
        }
    }
}

long LCD::getCurrentTime() {
    return currentTime;
}

long LCD::startCurrentTime() {
    currentTime = millis();
}

long LCD::getElapsedTime() {
    return millis() - currentTime;
}