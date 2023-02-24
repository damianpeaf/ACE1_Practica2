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

}

void loop()
{
  
  Wire.requestFrom(0x01,1);
  // leer lo que entra del esclavo
  while(Wire.available()){
    CODE = Wire.read();
  }
  Serial.println(CODE);
}