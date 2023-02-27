#include "Package.h"

//constructor
Package::Package(int color, int width, int height, int length){
  this->color = color;
  this->width = width;
  this->height = height;
  this->length = length;
}


void Package::getValues(){
  // function to send this values to the lcd
  Serial.println("Color: " + this->color);
}
