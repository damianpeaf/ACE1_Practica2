#include <LiquidCrystal.h>
#include "Menu.h"
#include "Wire.h" 

#define interrupt_signal_pin 2


void setup()
{
  Serial.begin(9600);
  // maestro
  Wire.begin();
  attachInterrupt(digitalPinToInterrupt(2), package_detection_request, RISING);
  initial_setup();
}

void loop()
{
  // start machine
  main_menu();
  
}

void package_detection_request(){
  Serial.println("INTERRUPCION RECIBIDA");
  send_package_request = true;
}
