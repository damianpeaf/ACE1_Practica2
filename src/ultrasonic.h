#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>


#define RIGHT_ULTRASONIC_TRIG  9
#define RIGHT_ULTRASONIC_ECHO  10


#define LEFT_ULTRASONIC_TRIG  12
#define LEFT_ULTRASONIC_ECHO  11
// TODO: Define the pins for the top|background? ultrasonic sensor

void ultrasonic_setup();

// Reference: Watching the sensor from the box entrance

int get_right_distance();

int get_left_distance();

#endif