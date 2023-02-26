#include <LiquidCrystal.h>
#include <Arduino.h>

#include "Menu.h"


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

const int buttonPin1 = 8;  // Pin del botón para avanzar
const int buttonPin2 = 9;  // Pin del botón para retroceder
int buttonState1 = 0;     // Estado del botón para avanzar
int buttonState2 = 0;     // Estado del botón para retroceder
int lastButtonState1 = 0; // Último estado del botón para avanzar
int lastButtonState2 = 0; // Último estado del botón para retroceder
int messageNum = 1;       // Número de mensaje actual

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



void initial_menu() {
  display_basic_menu(clockChar, "GRP 07 B ACE1", "Starting");
}

void ready_menu() {
  display_basic_menu(readyChar, "ready to start", "Press x for menu");
}

void statistics_menu() {
  display_basic_menu(clockChar, "Statistics", "");
}

void manage_menu() {
  buttonState1 = digitalRead(buttonPin1);  // Leer el estado actual del botón para avanzar
  buttonState2 = digitalRead(buttonPin2); 
  
    if (buttonState1 != lastButtonState1) {  // Si el estado del botón para avanzar ha cambiado
    if (buttonState1 == HIGH) {            // Si el botón para avanzar ha sido presionado
      messageNum++;                        // Cambiar al siguiente mensaje
      if (messageNum > 3) {                // Si ya se han mostrado los 3 mensajes
        messageNum = 1;                    // Volver al primer mensaje
      }
      lcd.clear();                         // Limpiar el LCD
      switch(messageNum) {                 // Seleccionar el mensaje a mostrar según el número
        case 1:
          lcd.print("Mensaje 1");
          break;
        case 2:
          lcd.print("Mensaje 2");
          break;
        case 3:
          lcd.print("Mensaje 3");
          break;
      }
    }
  }

  if (buttonState2 != lastButtonState2) {  // Si el estado del botón para retroceder ha cambiado
    if (buttonState2 == HIGH) {            // Si el botón para retroceder ha sido presionado
      messageNum--;                        // Cambiar al mensaje anterior
      if (messageNum < 1) {                // Si ya se han mostrado los 3 mensajes
        messageNum = 3;                    // Volver al último mensaje
      }
      lcd.clear();                         // Limpiar el LCD
      switch(messageNum) {                 // Seleccionar el mensaje a mostrar según el número
        case 1:
          lcd.print("Mensaje 1");
          break;
        case 2:
          lcd.print("Mensaje 2");
          break;
        case 3:
          lcd.print("Mensaje 3");
          break;
      }
    }
  }
  lastButtonState1 = buttonState1;   // Guardar el estado actual del botón para avanzar para la próxima iteración
  lastButtonState2 = buttonState2;   // Guardar el estado actual del botón para retroceder para la próxima iteración
}

// Scroll the message across the display
