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
    if (red_frequency >= 105 && red_frequency <= 177
    &&  green_frequency >= 149 && green_frequency <=235
    &&  blue_frequency >=171 && blue_frequency <= 308)  yellow_probability++;
    
    // ROJO 
    if (red_frequency >= 159 && red_frequency <= 288
    &&  green_frequency >= 150 && green_frequency <=440
    &&  blue_frequency >=236 && blue_frequency <= 375)  red_probability++;
    
    // Azul 
    if (red_frequency >= 164 && red_frequency <= 265
    &&  green_frequency >= 170 && green_frequency <=245
    &&  blue_frequency >=95 && blue_frequency <= 150)  blue_probability++;

    delay(200);
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