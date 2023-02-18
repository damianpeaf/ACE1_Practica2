#ifndef "Menu_h"
#define "Menu_h"

extern String initialMessage;
extern String readyMessage;
extern byte[8] clockChar;
extern byte[8] readyChar;

void menu_init();
void menu_print(String text);

#endif
