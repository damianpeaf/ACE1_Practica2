#ifndef Controllers_H
#define Controllers_H

// LIBRARIES

// Botons PINS
extern const int BTN_LEFT;
extern const int BTN_RIGHT;

// states
extern int buttons_mode;

// Button previous states
extern int last_btn_left_state;
extern int last_btn_right_state;




void initMenu();
void initiate_buttons();
void startMenu();


#endif