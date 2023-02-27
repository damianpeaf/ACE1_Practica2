#include "Package.h"


//constructor
Package::Package(int color, int widht, int height, int length){
  this->color = color;
  this->widht = widht;
  this->height = height;
  this->length = length;
}


void Package::getValues(){
  // function to send this values to the lcd
  Serial.println("COLOR RECIBIDO: " + String(this->color));
  Serial.println("ANCHO RECIBIDO: " + String(this->widht));
  Serial.println("ALTO RECIBIDO: " + String(this->height));
  Serial.println("LARGO RECIBIDO: " + String(this->length));
}
