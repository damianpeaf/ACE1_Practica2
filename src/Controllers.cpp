// #include "Controllers.h" 

// STATE 
const int buttons_mode = 0; // 1 = start menu, 2 = stop menu 
// button left
// button right
const int BTN_LEFT = 2;
const int BTN_RIGHT = 3;

// Button previous states
int last_btn_left_state = HIGH;
int last_btn_right_state = HIGH;

void initMenu(){
  if(digitalRead(BTN_LEFT) == LOW && last_btn_left_state == HIGH){

    Serial.println("START MENU");

    // TURN OFF READY LED
    // TURN ON WORKING LED
    // SHOW IN LCD -> "IZQ PARA PAUSAR" "DER PARA DETENER"
    // START MACHINE 
    buttons_mode = 1;
  }   

  last_btn_left_state = digitalRead(BTN_LEFT); 
}


void rightButtonMenu(){
    if(digitalRead(BTN_RIGHT) == LOW && last_btn_right_state == HIGH){
    Serial.println("STOP MENU");
    // STOP MACHINE
  }
}

void leftButtonMenu(){
  if(digitalRead(BTN_LEFT) == LOW && last_btn_left_state == HIGH){
  Serial.println("PAUSE MENU");
  // PAUSE MACHINE
  }
}

void startMenu() {
  // init_sequence();
  // START MACHINE  init_sequence();
  rightButtonMenu();
  leftButtonMenu();

  last_btn_left_state = digitalRead(BTN_LEFT);
  last_btn_right_state = digitalRead(BTN_RIGHT);
}


void initiate_buttons() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
}