
#include "ultrasonic.h"

void ultrasonic_setup() {
  pinMode(RIGHT_ULTRASONIC_TRIG, OUTPUT);
  pinMode(RIGHT_ULTRASONIC_ECHO, INPUT);


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

    Serial.print("Distancia desde la DERECHA: ");
    Serial.print(d);      
    Serial.print("cm");
    Serial.println();

    return d;
}