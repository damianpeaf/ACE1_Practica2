#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>


#define RIGHT_ULTRASONIC_TRIG  A3
#define RIGHT_ULTRASONIC_ECHO  A4


#define ABOVE_ULTRASONIC_TRIG  12
#define ABOVE_ULTRASONIC_ECHO  11
// TODO: Define the pins for the top|background? ultrasonic sensor

#define BACK_ULTRASONIC_TRIG  A1
#define BACK_ULTRASONIC_ECHO  A2

void ultrasonic_setup();

// Reference: Watching the sensor from the box entrance

int get_right_distance();

int get_above_distance();

int get_back_distance();

#endif