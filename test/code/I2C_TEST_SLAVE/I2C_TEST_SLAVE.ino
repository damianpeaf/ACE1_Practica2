#include <Wire.h>
const int POT = A0; // where the pot is connected

byte entry;
byte CODE; // This is the point to traslated messages
int state;
bool potOn = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // SLAVE CONFIGURATION
  Wire.begin(0x01); // This identify the arduino as the slave
  Wire.onReceive(entryRequest); // When we received from master
  Wire.onRequest(request);
}


void entryRequest(int re) { // this func recieved data from another place
  while (Wire.available()){
    entry = Wire.read();
    state = entry;
  }
  Serial.print(entry);
  Serial.println(" <- Value sent from master"); // Print what was read

}


void loop() {
  CODE = map(analogRead(POT), 0, 1023, 250, 750);
}


void request() { // If Master made a request, this func start
  Wire.write(CODE);
  Wire.endTransmission();
}