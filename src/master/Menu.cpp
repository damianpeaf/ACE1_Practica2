#include <LiquidCrystal.h>
#include <Arduino.h>

#include "Menu.h"
#include "LinkedList.h"

//MAESTRO
int not_recognized_packages = 0;
int reprocess_stages = 0;

bool send_package_request = false;

// ARRAY OF PACKAGES THAT ARE BEIGN SAVED  
int count = 0;
Package package;
LinkedList packagesList;
LinkedList sortPackagesList;


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

      print_screen("IZQ: PAUSE", "DER: END");

      while(true){

        // PAUSE
        if (is_left_button_pressed()) {
          Wire.beginTransmission(0x01);
          Wire.write(2); // PAUSE
          Wire.endTransmission();

          print_screen("IZQ: ", "CONTINUE");
          while (true) {
            if (is_left_button_pressed()) {
              Wire.beginTransmission(0x01);
              Wire.write(2); // RESUME
              Wire.endTransmission();
              print_screen("IZQ: PAUSE", "DER: END");
              break;
            }
          }
        }

        // END
        if (is_right_button_pressed()) {
          reprocess_menu();
          Wire.beginTransmission(0x01);
          Wire.write(1); // END
          Wire.endTransmission();
          statistics_menu();
          print_screen("IZQ:", "INICIAR");
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
      print_screen("IZQ:", "INICIAR");
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
      package = Package(color, width, height, length,width*height*length,count);
      packagesList.Insert(package);
      sortPackagesList.Insert(package);
      count++;
      // show the package values
      Serial.println("COLOR RECIBIDO: " + String(color));
      Serial.println("ANCHO RECIBIDO: " + String(width));
      Serial.println("ALTO RECIBIDO: " + String(height));
      Serial.println("LARGO RECIBIDO: " + String(length));
    }else{
      not_recognized_packages++;
      Serial.println("TOTAL PAQUETES NO RECONOCIDOS: " + String(not_recognized_packages));
      break;
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

      package = Package(color, width, height, length, width*height*length,count);
      package.setIsReprocessed(true);
      packagesList.Insert(package);
      sortPackagesList.Insert(package);
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
  reprocess_stages = not_recognized_packages;

  Serial.println("Pendientes: "+  String(not_recognized_packages));

  while(not_recognized_packages > 0){
    if(send_package_request){
      Serial.println("REPROCESANDO..........");
      reprocess_sequence_detection();
      print_screen("Pendientes: ", String(not_recognized_packages));
    }
    delay(500);
  }
}

void statistics_menu(){

  // * Número de etapas de reproceso de paquetes. 
  print_screen("Reprocess ", "stages: "+ String(reprocess_stages));

  bool end = false;

  while(!end){
    if(is_right_button_pressed()){

      //* Media y mediana del volumen total de paquetes identificados
      double media = 0;
      int mediana = 0;

      media = packagesList.getMedia();
      sortPackagesList.Sort();
      mediana = sortPackagesList.getMediana();

      print_screen("Media: " + String(media), "Mediana: " + String(mediana));

      int stage = 0;

      while(!end){
        if (is_right_button_pressed()){
        //* Cantidad de paquetes identificados por tipo (color) para cada etapa; se debe poder seleccionar la etapa a verificar (Lectura inicial, reproceso 1, ..., reproceso n).
        String stage_name = packagesList.getStageName(stage);
        int red = packagesList.getRed(stage);
        int yellow = packagesList.getYellow(stage);
        int blue = packagesList.getBlue(stage);
        lcd.clear();
        print_screen(stage_name, "R: "+String(red)+ " Y: "+ String(yellow)+ " B: "+ String(blue));

        while(!end){
          if(is_left_button_pressed()){
            // pass to the next stage
            stage++;
            if(stage >= count){
              stage = 0;
            }
            stage_name = packagesList.getStageName(stage);
            red = packagesList.getRed(stage);
            yellow = packagesList.getYellow(stage);
            blue = packagesList.getBlue(stage);
            lcd.clear();
            print_screen(stage_name, "R: "+String(red)+ " Y: "+ String(yellow)+ " B: "+ String(blue));
          }


          if (is_right_button_pressed()){
            // * Mostrar paquete por paquete los datos identificados para cada etapa, en orden de llegada; se debe poder seleccionar la etapa a verificar.
            stage = 0;

            stage_name = packagesList.getStageName(stage);
            String stage_color = packagesList.getColor(stage);
            Package package = packagesList.getPackage(stage);
            int stage_width = package.width;
            int stage_height = package.height;
            int stage_length = package.length;
            int stage_volume = package.volumen;

            lcd.clear();
            print_screen(stage_name + " C "+ stage_color, "W "+String(stage_width)+ " H "+ String(stage_height)+ " L "+ String(stage_length)+ " V "+ String(stage_volume));

            while(!end){
              if(is_left_button_pressed()){
                // pass to the next stage
                stage++;
                if(stage >= count){
                  stage = 0;
                }

                stage_name = packagesList.getStageName(stage);
                stage_color = packagesList.getColor(stage);
                package = packagesList.getPackage(stage);
                stage_width = package.width;
                stage_height = package.height;
                stage_length = package.length;
                stage_volume = package.volumen;
                
                lcd.clear();
                print_screen(stage_name + " C "+ stage_color, "W "+String(stage_width)+ " H "+ String(stage_height)+ " L "+ String(stage_length)+ " V "+ String(stage_volume));
              }

              if (is_right_button_pressed()){
                // * Media y mediana del volumen de los paquetes identificados por color de etiqueta.
                int color = 1;

                int media = packagesList.getColorVolumeMedia(color);
                int mediana = packagesList.getColorVolumeMediana(color);
                String color_name = "";

                switch(color){
                  case 1:
                    color_name = "RED";
                    break;
                  case 2:
                    color_name = "YELLOW";
                    break;
                  case 3:
                    color_name = "BLUE";
                    break;
                }

                lcd.clear();
                print_screen(color_name + " Media " + String(media), "Mediana " + String(mediana));

                while(!end){

                  if(is_left_button_pressed()){
                    color++;
                    if(color > 3){
                      color = 1;
                    }

                    media = packagesList.getColorVolumeMedia(color);
                    mediana = packagesList.getColorVolumeMediana(color);

                    switch(color){
                      case 1:
                        color_name = "RED";
                        break;
                      case 2:
                        color_name = "YELLOW";
                        break;
                      case 3:
                        color_name = "BLUE";
                        break;
                    }

                    lcd.clear();
                    print_screen(color_name + " Media " + String(media), "Mediana " + String(mediana));

                  }

                  if(is_right_button_pressed()){
                    end = true;
                  }
                }
              }
            }
          }
        }
      }
      }
    }
  }
}


bool is_right_button_pressed(){

  buttonStateRight = digitalRead(button_right);

  if (buttonStateRight != lastButtonStateRight && buttonStateRight == HIGH) {  // Si el estado del botón para avanzar ha cambiado
    lastButtonStateRight = buttonStateRight;
    Serial.println("BOTON DERECHO PRESIONADO");
    delay(100);
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
    delay(100);
    Serial.println("BOTON IZQUIERDO PRESIONADO");
    return true;
  }else{
    lastButtonStateLeft = buttonStateLeft;
    return false;
  }
}