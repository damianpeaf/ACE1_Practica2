
#include "ultrasonic.h"

void ultrasonic_setup() {
  pinMode(RIGHT_ULTRASONIC_TRIG, OUTPUT);
  pinMode(RIGHT_ULTRASONIC_ECHO, INPUT);

  pinMode(ABOVE_ULTRASONIC_TRIG, OUTPUT);
  pinMode(ABOVE_ULTRASONIC_ECHO, INPUT);

  pinMode(BACK_ULTRASONIC_TRIG, OUTPUT);
  pinMode(BACK_ULTRASONIC_ECHO, INPUT);

  digitalWrite(ABOVE_ULTRASONIC_TRIG, LOW);  
  digitalWrite(RIGHT_ULTRASONIC_TRIG, LOW);
  digitalWrite(BACK_ULTRASONIC_TRIG, LOW);
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

int get_above_distance(){
    long t; 
    long d;
    digitalWrite(ABOVE_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ABOVE_ULTRASONIC_TRIG, LOW);  
    t = pulseIn(ABOVE_ULTRASONIC_ECHO, HIGH);
    d = t/59;

    return d;
}

int get_back_distance(){
    long t; 
    long d;
    digitalWrite(BACK_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(BACK_ULTRASONIC_TRIG, LOW);  
    t = pulseIn(BACK_ULTRASONIC_ECHO, HIGH);
    d = t/59;

    return d;
}