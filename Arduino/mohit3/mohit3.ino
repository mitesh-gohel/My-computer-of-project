#include <Wire.h>

byte val = 0x01;

void setup()
{
  Wire.begin(); // join i2c bus
}

void loop()
{
  Wire.beginTransmission(32); // transmit to device #44 (0x2c)
                              // device address is specified in datasheet
  Wire.write(val);             // sends value byte  
  Wire.endTransmission();     // stop transmitting

  val = val << 1;
  delay(1000);
}
