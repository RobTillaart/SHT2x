//
//    FILE: SHT21_async.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: demo async interface
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
  uint16_t rawTemperature;
  uint16_t rawHumidity;

  start = micros();
  bool success  = sht.read();
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  if (success == false)
  {
    Serial.println("Failed read");
  }
  else
  {
    rawTemperature = sht.getRawTemperature();
    rawHumidity = sht.getRawHumidity();
    Serial.print(rawTemperature, HEX);
    Serial.print(" = ");
    Serial.print(sht.getTemperature(), 1);
    Serial.print("°C\t");
    Serial.print(rawHumidity, HEX);
    Serial.print(" = ");
    Serial.print(sht.getHumidity(), 1);
    Serial.print("%\t");
    Serial.println();
  }
}


// -- END OF FILE --
