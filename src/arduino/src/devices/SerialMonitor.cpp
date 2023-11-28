#include "SerialMonitor.h"

SerialMonitor::SerialMonitor() {
    lcd.init();
    lcd.backlight();
} 

void SerialMonitor::printText(String text) {
    lcd.print(text);
}

void SerialMonitor::setCursorDisplay(int x, int y) {
    lcd.setCursor(x, y);
}

void SerialMonitor::clearDisplay() {
    lcd.clear();
}