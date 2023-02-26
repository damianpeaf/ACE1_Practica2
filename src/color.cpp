#include "color.h"

int red_frequency = 0;
int green_frequency = 0;
int blue_frequency = 0;

int red_probability = 0;
int yellow_probability = 0;
int blue_probability = 0;


void color_setup(){
  pinMode(COLOR_S0, OUTPUT);
  pinMode(COLOR_S1, OUTPUT);
  pinMode(COLOR_S2, OUTPUT);
  pinMode(COLOR_S3, OUTPUT);
  pinMode(COLOR_OUTPUT, INPUT); // Configura el pin de salida del sensor de color
  
  digitalWrite(COLOR_S0,HIGH);
  digitalWrite(COLOR_S1,LOW);
  
}

void color_sequence() {

    // Configura el filtor ROJO para tomar lectura
    digitalWrite(COLOR_S2,LOW);
    digitalWrite(COLOR_S3,LOW);
    delay(100);

    red_frequency= pulseIn(COLOR_OUTPUT, LOW);
    delay(100);

    // Configura el filtor VERDE para tomar lectura
    digitalWrite(COLOR_S2,HIGH);
    digitalWrite(COLOR_S3,HIGH);
    delay(100);
    green_frequency = pulseIn(COLOR_OUTPUT, LOW);
    delay(100);

    // Configura el filtor AZUL para tomar lectura
    digitalWrite(COLOR_S2,LOW);
    digitalWrite(COLOR_S3,HIGH);
    delay(100);
    blue_frequency = pulseIn(COLOR_OUTPUT, LOW);
    delay(100);

    // Serial.print( "Red: " + String(red_frequency));
    // Serial.print(" Green: " + String(green_frequency));
    // Serial.print(" Blue: " + String(blue_frequency));
    // Serial.println();

    // AMARILLO 
    if (red_frequency >= 50 && red_frequency <= 150
    &&  green_frequency >= 90 && green_frequency <=160
    &&  blue_frequency >=160 && blue_frequency <= 220)  yellow_probability++;
    
    // ROJO 
    if (red_frequency >= 100 && red_frequency <= 200
    &&  green_frequency >= 200 && green_frequency <=400
    &&  blue_frequency >=250 && blue_frequency <= 350)  red_probability++;
    
    // Azul 
    if (red_frequency >= 120 && red_frequency <= 200
    &&  green_frequency >= 80 && green_frequency <=210
    &&  blue_frequency >=50 && blue_frequency <= 130)  blue_probability++;

    delay(100);
}

void reset_color_probabilities(){
    red_probability = 0;
    yellow_probability = 0;
    blue_probability = 0;
}

int resultant_color(){

    if (red_probability > yellow_probability && red_probability > blue_probability) return 1; // RED
    if (yellow_probability > red_probability && yellow_probability > blue_probability) return 2; // YELLOW
    if (blue_probability > red_probability && blue_probability > yellow_probability) return 3; // BLUE

    // DEFAULT: No color detected
    return 0;
}