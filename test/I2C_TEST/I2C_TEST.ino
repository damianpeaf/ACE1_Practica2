#include "Wire.h" 
//MAESTRO
byte CODE;
byte respuesta;
void setup()
{
  Serial.begin(9600);
  // maestro
  Wire.begin();
   // preguntar al esclavo

    int value = 20;
    Wire.beginTransmission(0x01);
    Wire.write(value);
    Wire.endTransmission();
}

void loop()
{
  
  Wire.requestFrom(0x01,1);
  // leer lo que entra del esclavo
  while(Wire.available()){
    CODE = Wire.read();
  }

  if(CODE != 0){
    Serial.println(CODE);
    Wire.beginTransmission(0x01);
    Wire.write(1);
    Wire.endTransmission();
  }

}