#include <Wire.h> 

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // Start the communication

}
byte pin[] = {2,3,4,5,6};
byte state = 0;

void slave(){
  for(int i = 0; i< 5; ii+){
    //
    Wire.beginTransmission(123); // this is the address of the slave
    Wire.write(pin[i]); // write in the pin of the slave
    Wire.write(state); // send data
    Wire.endTransmission(); // Stop transmission
    delay(1000);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  slave();
}
