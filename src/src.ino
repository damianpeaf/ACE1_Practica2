
// ----- SLAVE ----- //
/*
    Código fuente - Práctica 2 - Arquitectura de Computadores y Ensambladores 1
    Grupo:  07
    Integrantes:
        - Alvaro Norberto García Meza 202109567
        - Damián Ignacio Peña Afre 202110568
        - Daniel Estuardo Cuque Ruíz 202112145
        - José Manuel Ibarra Pirir 202001800
*/

#include <Servo.h>
#include "Wire.h" 
#include "motors.h"
#include "color.h"
#include "ultrasonic.h"

// Servos
Servo servo_1;
Servo servo_2;
int pos1 = 0;  // Variable para almacenar la posición del servo 1
int pos2 = 0;  // Variable para almacenar la posición del servo 2


// INTERRUPT
#define interrupt_signal_pin 0
bool have_to_send = false;
bool have_to_init = false;
bool have_to_pause = false;

// Package props
byte package_color;
byte package_width;
byte package_height;
byte package_length;

// Package detection
unsigned long package_aligment_time = 0;
unsigned long stop_motor_time = 0;
int posible_package_count_right = 0;
int realigment_tries = 0;


void setup() {
    Serial.begin(9600);

    ultrasonic_setup();
    color_setup();
    motor_setup();
    stop_motor();

    // ESCLAVO
    Wire.begin(0x01);
    Wire.onRequest(send_package_info);
    Wire.onReceive(receive_info);

    // INTERRUPT
    pinMode(interrupt_signal_pin, OUTPUT);
    digitalWrite(interrupt_signal_pin, LOW);

    // SERVOS
    servo_1.attach(10);
    servo_2.attach(9);
    servo_1.write(0);
    servo_2.write(0);
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
        Serial.println("POSSIBLE PACKAGE");   
    }

    if(posible_package_count_right >= 4){
        posible_package_count_right = 0;
        Serial.println("OBJECT DETECTED");

        // Package aligment
        package_aligment_time = millis();
        move_motor();
        while (millis() - package_aligment_time <  80) {}
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
            
            if(color == 1){
                servo_1.write(0);
            }else if(color == 2){
                servo_2.write(0);
            }else if(color == 3){
                servo_2.write(180);
            }

            int width = 13 - right_distance;
            if (width < 2) {
                width = 2;
            }else if(width > 10){
                width = 10;
            }

            // move to sensor above
            int above_distance = get_above_distance();
            while(above_distance >= 15){
                move_motor();
                above_distance = get_above_distance();
            }
            int average_above_distance = above_distance;


            int back_distance = get_back_distance();

            int height = 18 - average_above_distance;
            if (height < 2) {
                height = 2;
            }else if(height > 10){
                height = 10;
            }

            int length = 52-back_distance;
            if(length < 2){
                length = 2;
            }else if(length > 10){
                length = 10;
            }

            package_color = color;
            package_width = width;
            package_height = height;
            package_length = length;

            have_to_send = true;


            if (package_color == 1) {
                delay(500);
                stop_motor();
                delay(700);
                servo_1.write(180);
                delay(700);
                servo_1.write(0);
                delay(700);
            }else if (package_color == 2) {
                delay(1000);
                stop_motor();
                delay(700);
                servo_2.write(180);
                delay(700);
                servo_2.write(0);
                delay(700);
            }else if (package_color == 3) {
                delay(1000);
                stop_motor();
                delay(700);
                servo_2.write(0);
                delay(700);
                servo_2.write(180);
                delay(700);
            }
        }else{
            // NOT RECOGNIZED PACKAGE
            have_to_send = true;

            Serial.println("NOT RECOGNIZED PACKAGE");
            package_color = 0;  
            package_width = 0;
            package_height = 0;
            package_length = 0;
        }

        move_motor();
        delay(1000);
        right_distance = get_right_distance();
        Serial.println("END OF SEQUENCE");
    }

    delay(100);

    // Send interrupt signal
    if(have_to_send){
        have_to_send = false;
        Serial.println("INTERRUPT SIGNAL");
        digitalWrite(interrupt_signal_pin, LOW);
        delay(20);
        digitalWrite(interrupt_signal_pin, HIGH);
        delay(20);
        digitalWrite(interrupt_signal_pin, LOW);
        delay(50);
    }

    if(have_to_pause){
        stop_motor();
        while(have_to_pause){
            delay(100);
        }
    }
}

void loop() {
    while(have_to_init){
        move_motor();
        init_sequence();
    }
    stop_motor();
}

void send_package_info()
{
    Serial.println("SEND");
    Wire.write(package_color);
    Wire.write(package_width);
    Wire.write(package_height);
    Wire.write(package_length);
}

void receive_info(int howMany) {
  while (Wire.available()) {
    int option = Wire.read();

    if(option == 0){
        Serial.println("CONNECTED");
    }else if(option == 1){
        Serial.println("INIT/STOP");
        have_to_init = !have_to_init;
    }else if(option == 2){
        have_to_pause = !have_to_pause;
    }

  }
}