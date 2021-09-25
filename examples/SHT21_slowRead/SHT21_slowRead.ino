//
//    FILE: SHT21_slowRead.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT21


#include "Wire.h"
#include "SHT21.h"

#define SHT21_ADDRESS   0x44

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

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  start = micros();
  sht.read(false);         // default = true/fast       slow = false
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
