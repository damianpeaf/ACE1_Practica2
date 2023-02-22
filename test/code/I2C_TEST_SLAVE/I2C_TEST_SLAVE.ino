#include <Wire.h>
const int POT = A0; // where the pot is connected

byte entry = 0;
byte CODE; // This is the point to traslated messages

void setup() {
  // put your setup code here, to run once:
  
  // SLAVE CONFIGURATION
  Wire.begin(0x01); // This identify the arduino as the slave
  Wire.onReceive(entryRequest); // This is 
  Wire.onRequest(request); // The master is asking for data 
}
void request() { // If Master made a request, this func start
  Wire.write(CODE);
}

void entryRequest(int re) { // this func recieved data from another place
  while(Wire.available()) {
    entry = Wire.read();
  }
  Serial.println(entry); // Print what was read
}


void loop() {

  CODE = map(analogRead(POT),0,1023,250,750);
}


