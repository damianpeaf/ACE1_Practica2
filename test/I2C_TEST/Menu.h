#ifndef Menu_h
#define Menu_h

extern LiquidCrystal lcd;

extern String initialMessage;
extern String readyMessage;
extern int actualTime;
extern byte clockChar[8];
extern byte readyChar[8];
const int buttonPin1; // Pin del botón para avanzar
const int buttonPin2;  // Pin del botón para retroceder
int buttonState1;     // Estado del botón para avanzar
int buttonState2;     // Estado del botón para retroceder
int lastButtonState1; // Último estado del botón para avanzar
int lastButtonState2; // Último estado del botón para retroceder
int messageNum;       // Número de mensaje actual

void initial_menu();
void ready_menu();
void statistics_menu();
void manage_menu();
void initial_setup();

#endif
