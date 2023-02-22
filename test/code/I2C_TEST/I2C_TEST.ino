#include <Wire.h> 
byte CODE; // This is the point to traslated messages

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // Start the communication, here is the master
  Serial.begin(9600);
  Serial.println("From Master, and the I2C was set");
}

void loop() {
  // put your main code here, to run repeatedly:
  String STRING = "";

  // Request data from the slave 
  Wire.requestFrom(0x01,1); // From the slave address, only 1 data transfer, this may vary
  while(Wire.available()){ // While both arduino's are connected...
    CODE = Wire.read(); // read the code that is being transferred
  }
  
  Serial.println("From the slave the value of the pot is " + CODE);
}
