/*
    Código fuente - Práctica 2 - Arquitectura de Computadores y Ensambladores 1
    Grupo:  07
    Integrantes:
        - Alvaro Norberto García Meza 202109567
        - Damián Ignacio Peña Afre 202110568
        - Daniel Estuardo Cuque Ruíz 202112145
        - José Manuel Ibarra Pirir 202001800
*/

#include <LiquidCrystal.h>

#include "Menu.h"
#include "motors.h"
#include "color.h"
#include "ultrasonic.h"


unsigned long package_aligment_time = 0;
unsigned long stop_motor_time = 0;

void setup() {
    Serial.begin(9600);

    ultrasonic_setup();
    color_setup();
    motor_setup();
    move_motor();

}

void init_sequence(){

    int right_distance = get_right_distance();

    if(right_distance <= 12){

        Serial.print("OBJECT DETECTED");

        package_aligment_time = millis();
        move_motor();
        while (millis() - package_aligment_time <  200) {}

        stop_motor();
        Serial.println("MOTOR STOP !!!");

        stop_motor_time = millis();
        reset_color_probabilities();
        while (millis() - stop_motor_time <  5000) {
            color_sequence();
        }

        int color = resultant_color();

        if(color == 1){
            Serial.println("RED");
        } else if(color == 2){
            Serial.println("YELLOW");
        } else if(color == 3){
            Serial.println("BLUE");
        }else{
            Serial.println("NO COLOR");
        }

        move_motor();
        if(color != 0){
            delay(1000);
            // TODO: left ultrasonic sensor
        }else{
            delay(100);
        }
    }


    delay(100);

}

void loop() {

    init_sequence();

}