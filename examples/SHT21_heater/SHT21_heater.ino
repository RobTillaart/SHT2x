//
//    FILE: SHT21_heater.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo heater functions
//     URL: https://github.com/RobTillaart/SHT21


#include "Wire.h"
#include "SHT21.h"

#define SHT21_ADDRESS   0x40

SHT21 sht;
uint8_t status;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT21_LIB_VERSION: \t");
  Serial.println(SHT21_LIB_VERSION);

  Wire.begin();
  sht.begin(SHT21_ADDRESS);
  Wire.setClock(100000);

  sht.setHeatTimeout(30);  // heater timeout 30 seconds, just for demo.

  status = sht.getStatus();
  printHeaterStatus(status);

  sht.heatOn();

  while (sht.isHeaterOn())
  {
    status = sht.getStatus();
    printHeaterStatus(status);
    sht.read();
    Serial.println(sht.getTemperature());
    delay(10000);
  }

  Serial.println("switched off");
}


void loop()
{
  // forced switch off
  if (status & SHT21_STATUS_HEATER_ON) sht.heatOff();
}


void printHeaterStatus(uint16_t status)
{
  Serial.print(millis());
  Serial.print("\tHEATER: ");
  if (status & SHT21_STATUS_HEATER_ON)
  {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}


// -- END OF FILE --
