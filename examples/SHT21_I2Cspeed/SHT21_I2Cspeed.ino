//
//    FILE: SHT21_I2Cspeed
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: testing the performance at different I2C speeds
//     URL: https://github.com/RobTillaart/SHT21


#include "Wire.h"
#include "SHT21.h"

#define SHT21_ADDRESS   0x40

uint32_t start;
uint32_t stop;

SHT21 sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT21_LIB_VERSION: \t");
  Serial.println(SHT21_LIB_VERSION);

  Wire.begin();
  sht.begin(SHT21_ADDRESS);
  Wire.setClock(100000);

  uint8_t stat = sht.getStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  for (uint32_t I2Cfreq = 100000; I2Cfreq < 600000; I2Cfreq += 50000)
  {
    Serial.print(I2Cfreq/1000);
    Wire.setClock(I2Cfreq);
    test();
  }
}


void test()
{
  start = micros();
  sht.read();
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(100);
}


// -- END OF FILE --
