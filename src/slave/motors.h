#ifndef Motors_h
#define Motors_h

#include <Arduino.h>

#define MOTOR1_IN1 A0
#define MOTOR1_IN2 13
#define MOTOR1_ENA 3
#define MOTOR1_VEL 255

void motor_setup();

void move_motor();

void stop_motor();

void move_motor_backwards();

#endif