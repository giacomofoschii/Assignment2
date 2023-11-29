#ifndef __CONFIG__
#define __CONFIG__

#define LED_1 8
#define LED_2 3
#define LED_3 4

#define BUT_1 5
#define TRIG_PIN 10
#define ECHO_PIN 11
#define GATE_PIN 9
#define PIR_PIN 2
#define TEMP_PIN A1
#define LCD_SDA_PIN A4
#define LCD_SCL_PIN A5
#define LCD_PIN 13

#define N1 3000
#define N2 4000
#define N3 10000
#define N4 2000
#define BLINK_INT1 0.1
#define BLINK_INT2 0.5

#define MINDIST 5
#define MAXDIST 10
#define MAXTEMP 40
#define MAXTIME 10000

enum State {SLEEPING, CHECK_IN, ENTERING, READY, WASHING, ERROR, FINISHED, CHECK_OUT};
static State state = SLEEPING;

#endif
