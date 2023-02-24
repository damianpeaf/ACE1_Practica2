#include "Wire.h" 

#define interrupt_signal_pin 2

//MAESTRO
byte CODE;
byte respuesta;

bool send_package_request = false;
void setup()
{
  Serial.begin(9600);
  // maestro
  Wire.begin();

  attachInterrupt(digitalPinToInterrupt(2), package_detection_request, RISING);

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // Start the communication, here is the master
  Serial.begin(9600);
  Serial.println("From Master, and the I2C was set");
  sendDataToSlave();
}

void loop()
{
  
  delay(1000);

  if(send_package_request){
    Wire.requestFrom(0x01, 4);
    while (Wire.available()) {
      int color = Wire.read();
      int width = Wire.read();
      int height = Wire.read();
      int length = Wire.read();

      Serial.println("COLOR RECIBIDO: " + String(color));
      Serial.println("ANCHO RECIBIDO: " + String(width));
      Serial.println("ALTO RECIBIDO: " + String(height));
      Serial.println("LARGO RECIBIDO: " + String(length));
      
    }
    send_package_request = false;
  }

}


void package_detection_request(){
  Serial.println("INTERRUPCION RECIBIDA");
  send_package_request = true;
}
