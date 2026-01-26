//    FILE: SHT2x_AH_issue42.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test effect of Wifi on RH and T
//     URL: https://github.com/RobTillaart/SHT2x/issues/42

#include "Arduino.h"

//  from Temperature Library
float absoluteHumidity(float Celsius, float relHumidity)
{
  float TC = Celsius;
  float AH = (2.1674 * 6.112) * relHumidity;
  AH *= exp((17.67 * TC)/(243.5 + TC));
  AH /=  (273.15 + TC);
  return AH;
}


void setup() 
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);

  //  Test 1-2
 Serial.println("03 cm, Temp = 23.6, Hum = 34.4");
 Serial.println(absoluteHumidity(23.6, 34.4));
 Serial.println("15 cm, Temp = 23.4, Hum = 32.2");
 Serial.println(absoluteHumidity(23.4, 32.2));
 Serial.println();

  //  Test 3-4
 Serial.println("03 cm, Temp = 25.6, Hum = 24.0");
 Serial.println(absoluteHumidity(25.6, 24.0));
 Serial.println("15 cm, Temp = 22.6, Hum = 28.3");
 Serial.println(absoluteHumidity(22.6, 28.3));
 Serial.println();
}

void loop()
{


}

// -- END OF FILE --
