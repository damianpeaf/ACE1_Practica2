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

    //HAY QUE CALIBRARLO MANUALMENTE 
    

    // AMARILLO 
    if (red_frequency >= 118 && red_frequency <= 175
    &&  green_frequency >= 166 && green_frequency <=234
    &&  blue_frequency >=230 && blue_frequency <= 310)  yellow_probability++;
    
    // Azul 
    if (red_frequency >= 191 && red_frequency <= 260
    &&  green_frequency >= 91 && green_frequency <=311
    &&  blue_frequency >=107 && blue_frequency <= 147)  blue_probability++;
    
    
    // ROJO 
    if (red_frequency >= 197 && red_frequency <= 283
    &&  green_frequency >= 150 && green_frequency <=518
    &&  blue_frequency >=258 && blue_frequency <= 334)  red_probability++;
    
    

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