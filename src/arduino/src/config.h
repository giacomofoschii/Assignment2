#ifndef __CONFIG__
#define __CONFIG__

#define LED_1 2
#define LED_2 3
#define LED_3 4

#define BUT_1 5
#define TRIG_PIN 8
#define ECHO_PIN 9
#define GATE_PIN 10
#define PIR_PIN 11
#define TEMP_PIN A1

#define N1 3000
#define N2 4000
#define N3 10000
#define N4 2000
#define BLINK_INT1 0.1
#define BLINK_INT2 0.5

#define MINDIST
#define MAXDIST
#define MAXTEMP 40
#define MAXTIME 10000

enum State{ SLEEPING, CHECK_IN, ENTERING, READY, WASHING, ERROR, FINISHED, CHECK_OUT};

#endif
