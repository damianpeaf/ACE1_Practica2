#include "color.h"

int red_frequency = 0;
int green_frequency = 0;
int blue_frequency = 0;

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
    Serial.print(" R= "); Serial.print(red_frequency);
    delay(100);

    // Configura el filtor VERDE para tomar lectura
    digitalWrite(COLOR_S2,HIGH);
    digitalWrite(COLOR_S3,HIGH);
    delay(100);
    green_frequency = pulseIn(COLOR_OUTPUT, LOW);
    Serial.print(" V= "); Serial.print(green_frequency);
    delay(100);

    // Configura el filtor AZUL para tomar lectura
    digitalWrite(COLOR_S2,LOW);
    digitalWrite(COLOR_S3,HIGH);
    delay(100);
    blue_frequency = pulseIn(COLOR_OUTPUT, LOW);
    Serial.print(" A= "); Serial.print(blue_frequency);
    delay(100);

    //HAY QUE CALIBRARLO MANUALMENTE 
    // ! Pendiente de pruebas
    if (red_frequency < 85 && green_frequency > 80 && blue_frequency > 80)  Serial.print(" . * ROJO **");
    if (red_frequency > 80 && green_frequency > 100 && blue_frequency < 80)  Serial.print(" . * AZUL **");
    if (red_frequency > 185 && green_frequency < 140 && blue_frequency < 130)  Serial.print(" . * AMARILLO **");

    Serial.println("*");
    delay(200);
}