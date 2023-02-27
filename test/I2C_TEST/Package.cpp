#include "Package.h"

//constructor
Package::Package(int color, int width, int height, int lengt){
  this->color = color;
  this->width = width;
  this->height = height;
  this->length = length;
}

Package::Package(){
  this->color = 0;
  this->width = 0;
  this->height = 0;
  this->length = 0;
}

void Package::getValues(){
  // function to send this values to the lcd
  Serial.println("Color: " + this->color);
}
