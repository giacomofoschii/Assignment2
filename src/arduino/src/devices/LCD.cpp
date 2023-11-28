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