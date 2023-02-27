#include <LiquidCrystal.h>
#include <Arduino.h>

#include "Menu.h"

// PACKAGES
const int PENDANT_PACKAGES = 0;

//MAESTRO
int not_recognized_packages = 0;

bool send_package_request = false;

// ARRAY OF PACKAGES THAT ARE BEIGN SAVED  
int count = 0;
const int ARRAY_SIZE = 10;
Package packagesArray[ARRAY_SIZE];


LiquidCrystal lcd(7,6,5,4,3,10); // RS, E, D4, D5, D6, D7


byte clockChar[8] = {
  B11111,
  B01010,
  B01010,
  B00100,
  B01010,
  B01010,
  B11111,
  B00000,
};

byte readyChar[8] = {
  B00000,
  B11011,
  B01010,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000
};

const int button_right = 9;  // Pin del botón para avanzar
const int button_left = 8;  // Pin del botón para retroceder
int buttonStateRight = 0;     // Estado del botón para avanzar
int buttonStateLeft = 0;     // Estado del botón para retroceder
int lastButtonStateRight = 0; // Último estado del botón para avanzar
int lastButtonStateLeft = 0; // Último estado del botón para retroceder
int messageNum = 1;       // Número de mensaje actual

void initial_setup() {
  pinMode(button_right,INPUT);
  pinMode(button_left,INPUT);
  initial_menu();
}

void display_basic_menu(uint8_t* customChar, String message, String prompt) {
  lcd.begin(16,2);
  lcd.createChar(0, customChar);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.print(message);
  lcd.write(byte(0));

  lcd.setCursor(0,1);
  lcd.print(prompt);
}

void print_screen(String line1, String line2) {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

void initial_menu() {
  display_basic_menu(clockChar, "GRP 07 B ACE1", "Starting");
  delay(4000);
  Wire.beginTransmission(0x01);
  Wire.write(0);
  Wire.endTransmission();
  delay(1000);
  display_basic_menu(readyChar, "Conexión", "establecida");
  delay(1000);
  display_basic_menu(readyChar, "ready to start", "Press x for menu");
}


void manage_menu() {
  while(true){
    if (is_left_button_pressed()) {
      
      count = 0;
      Wire.beginTransmission(0x01);
      Wire.write(1); // START
      Wire.endTransmission();

      print_screen("IZQ: PAUSE", "DER: END")

      while(true){

        // PAUSE
        if (is_left_button_pressed()) {
          Wire.beginTransmission(0x01);
          Wire.write(2); // PAUSE
          Wire.endTransmission();

          print_screen("IZQ: ", "CONTINUE")
          while (true) {
            if (is_left_button_pressed()) {
              Wire.beginTransmission(0x01);
              Wire.write(2); // RESUME
              Wire.endTransmission();
              print_screen("IZQ: PAUSE", "DER: END")
              break;
            }
          }
        }

        // END
        if (is_right_button_pressed()) {
          reprocess_menu();
          // TODO: stats
          Wire.beginTransmission(0x01);
          Wire.write(1); // START
          Wire.endTransmission();
          print_screen("IZQ:", "INICIAR")
          break;
        }

        
        // SLAVE DETECTING PACKAGES
        if(send_package_request){
          initial_sequence_detection();    
        }
      }

    }
  }
}

void main_menu(){
  
  while(true){
    if(is_left_button_pressed()){
      print_screen("IZQ:", "INICIAR")
      manage_menu();
    }
  }
}

void initial_sequence_detection(){
  Wire.requestFrom(0x01, 4);
  while (Wire.available()) {
    int color = Wire.read();

    if(color != 0){
      int width = Wire.read();
      int height = Wire.read();
      int length = Wire.read();
      // create a new package
      // save the package in the array
      packagesArray[count] = Package(color, width, height, length);
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

void reprocess_sequence_detection(){
  Wire.requestFrom(0x01, 4);
  while (Wire.available()) {
    int color = Wire.read();

    if(color != 0){
      int width = Wire.read();
      int height = Wire.read();
      int length = Wire.read();

      packagesArray[count] = Package(color, width, height, length, true);
      count++;

      Serial.println("COLOR RECIBIDO: " + String(color));
      Serial.println("ANCHO RECIBIDO: " + String(width));
      Serial.println("ALTO RECIBIDO: " + String(height));
      Serial.println("LARGO RECIBIDO: " + String(length));
      not_recognized_packages--;
    }
  }
  send_package_request = false;
}


void reprocess_menu(){
  print_screen("Pendientes: ", String(not_recognized_packages));

  while(not_recognized_packages > 0){
    if(send_package_request){
      reprocess_sequence_detection();
      print_screen("Pendientes: ", String(not_recognized_packages));
    }
  }
}

void statistics_menu(){

}

bool is_right_button_pressed(){

  buttonStateRight = digitalRead(button_right);

  if (buttonStateRight != lastButtonStateRight && buttonStateRight == HIGH) {  // Si el estado del botón para avanzar ha cambiado
    lastButtonStateRight = buttonStateRight;
    Serial.println("BOTON DERECHO PRESIONADO");
    return true;
  }else{
    lastButtonStateRight = buttonStateRight;
    return false;
  }
}

bool is_left_button_pressed(){

  buttonStateLeft = digitalRead(button_left);

  if (buttonStateLeft != lastButtonStateLeft && buttonStateLeft == HIGH) {  // Si el estado del botón para avanzar ha cambiado
    lastButtonStateLeft = buttonStateLeft;
    Serial.println("BOTON IZQUIERDO PRESIONADO");
    return true;
  }else{
    lastButtonStateLeft = buttonStateLeft;
    return false;
  }
}