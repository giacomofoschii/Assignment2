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
        if(getElapsedTime() - getCurrentTime() >= 1000) {
        setCursorDisplay(11, 1);
        printText(String(seconds));
        startCurrentTime();
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