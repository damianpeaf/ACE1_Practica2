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
int posible_package_count_right = 0;
int realigment_tries = 0;

void setup() {
    Serial.begin(9600);

    ultrasonic_setup();
    color_setup();
    motor_setup();
    move_motor();

}

void color_detection(){
    // Color detection
    stop_motor_time = millis();
    reset_color_probabilities();
    while (millis() - stop_motor_time <  1500) {
        color_sequence();
    }
}

void color_realign(){
    move_motor();
    delay(200);
    stop_motor();
    color_detection();
    int color = resultant_color();

    realigment_tries++;
    if(color == 0 && realigment_tries < 3){
        color_realign();
    }
}

void init_sequence(){

    int right_distance = get_right_distance();

    if(right_distance <= 11){
        posible_package_count_right++;      
    }

    if(posible_package_count_right >= 3){
        posible_package_count_right = 0;
        Serial.println("OBJECT DETECTED");

        // Package aligment
        package_aligment_time = millis();
        move_motor();
        while (millis() - package_aligment_time <  100) {}
        stop_motor();
        right_distance = get_right_distance();


        // Color detection
        color_detection();
        move_motor();
        int color = resultant_color();

        // Realign package
        if(color == 0){
            realigment_tries = 0;
            color_realign();
            move_motor();
        }

        if(color != 0){
            int width = 13 - right_distance;
            if (width < 2) {
                width = 2;
            }
            // TODO: Servo
            Serial.println("Color: " + String(color) + " Width: " + String(width));
            
        }else{
            // NOT RECOGNIZED PACKAGE
            Serial.println("NOT RECOGNIZED PACKAGE");
        }

        // Move to next package
        while (right_distance > 11){
            right_distance = get_right_distance();
        }
    }

    delay(100);

}

void loop() {

    init_sequence();
}