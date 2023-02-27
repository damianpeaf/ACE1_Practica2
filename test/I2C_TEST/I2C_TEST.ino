#include "Wire.h" 
#include "Menu.h"
#include "Controllers.h"
#include "Package.h"

#define interrupt_signal_pin 2

// LCD
LiquidCrystal lcd(2,3,4,5,6,7); // RS, E, D4, D5, D6, D7

//MAESTRO
byte CODE;
byte respuesta;
int not_recognized_packages = 0;

bool send_package_request = false;

// ARRAY OF PACKAGES THAT ARE BEIGN SAVED  
const int count = 0;
const int ARRAY_SIZE = 10;
Package packages[ARRAY_SIZE];


void setup()
{
  Serial.begin(9600);
  // maestro
  Wire.begin();

  attachInterrupt(digitalPinToInterrupt(2), package_detection_request, RISING);
}

void init_mode(){
  Serial.println("INIT MODE");
  initial_menu();
  delay(5000);
  while(buttons_mode != 1){
    // Show to press x to start
    startMenu();
    // Wait a response from a button
    initMenu();
  }
}
void loop()
{
  // start machine
  init_mode();
  
  delay(1000);
  if(send_package_request){
    Wire.requestFrom(0x01, 4);
    while (Wire.available()) {
      int color = Wire.read();

      if(color != 0){
        int width = Wire.read();
        int height = Wire.read();
        int length = Wire.read();
        // create a new package
        Package package(color, width, height, length);
        // save the package in the array
        packages[count] = package;
        count++;
        // show the package values
        Serial.println("COLOR RECIBIDO: " + String(color));
        Serial.println("ANCHO RECIBIDO: " + String(width));
        Serial.println("ALTO RECIBIDO: " + String(height));
        Serial.println("LARGO RECIBIDO: " + String(length));
      }else{
        not_recognized_packages++;
        Serial.println("TOTAL PAQUETES NO RECONOCIDOS: " + String(not_recognized_packages));
      }

    }
    send_package_request = false;
  }
}


void package_detection_request(){
  Serial.println("INTERRUPCION RECIBIDA");
  send_package_request = true;
}
