#ifndef Menu_h
#define Menu_h

#include "Arduino.h"
#include <Wire.h>
#include "Package.h"

extern LiquidCrystal lcd;

extern String initialMessage;
extern String readyMessage;
extern int actualTime;
extern byte clockChar[8];
extern byte readyChar[8];
extern const int buttonPin1; // Pin del botón para avanzar
extern const int buttonPin2;  // Pin del botón para retroceder
extern int buttonState1;     // Estado del botón para avanzar
extern int buttonState2;     // Estado del botón para retroceder
extern int lastButtonState1; // Último estado del botón para avanzar
extern int lastButtonState2; // Último estado del botón para retroceder
extern int messageNum;       // Número de mensaje actual
extern bool send_package_request;


void initial_menu();
void ready_menu();
void statistics_menu();
void manage_menu();
void initial_setup();
void print_screen();
bool is_right_button_pressed();
bool is_left_button_pressed();

#endif
