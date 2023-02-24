
#include "ultrasonic.h"

void ultrasonic_setup() {
  pinMode(RIGHT_ULTRASONIC_TRIG, OUTPUT);
  pinMode(RIGHT_ULTRASONIC_ECHO, INPUT);

  pinMode(LEFT_ULTRASONIC_TRIG, OUTPUT);
  pinMode(LEFT_ULTRASONIC_ECHO, INPUT);

  digitalWrite(LEFT_ULTRASONIC_TRIG, LOW);  
  digitalWrite(RIGHT_ULTRASONIC_TRIG, LOW);
}


int get_right_distance(){
    long t; 
    long d;
    digitalWrite(RIGHT_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(RIGHT_ULTRASONIC_TRIG, LOW);  
    t = pulseIn(RIGHT_ULTRASONIC_ECHO, HIGH);
    d = t/59;

    return d;
}

int get_left_distance(){
    long t; 
    long d;
    digitalWrite(LEFT_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(LEFT_ULTRASONIC_TRIG, LOW);  
    t = pulseIn(LEFT_ULTRASONIC_ECHO, HIGH);
    d = t/59;

    return d;
}