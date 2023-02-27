#include "Package.h"

//constructor
Package::Package(int color, int width, int height, int length){
  this->color = color;
  this->width = width;
  this->height = height;
  this->length = length;
}

Package::Package(int color, int width, int height, int length, bool isReprocessed){
  this->color = color;
  this->width = width;
  this->height = height;
  this->length = length;
  this->isReprocessed = isReprocessed;
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
