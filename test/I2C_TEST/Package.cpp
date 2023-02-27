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
  Serial.println("Color: " + this->color);
}
