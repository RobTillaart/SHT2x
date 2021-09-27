//
//    FILE: SHT21_nolib.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test sensor without library
//     URL: https://github.com/RobTillaart/SHT21


#include "Wire.h"

#define SHT_ADDRESS   0x40


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(100000);

  testConnected();
}


void loop()
{
  delay(1000);
  float t = getTemperature();
  Serial.println(t, 1);
  delay(1000);
  float h = getHumidity();
  Serial.println(h, 1);
}

///////////////////////////////////////////////////

void testConnected()
{
  Wire.beginTransmission(SHT_ADDRESS);
  int rv = Wire.endTransmission();
  if (rv != 0) Serial.println("SHT21_ERR_NOT_CONNECT");
  else Serial.println("CONNECTED");
}


float getTemperature()
{
  uint16_t raw = 0;

  Wire.beginTransmission(SHT_ADDRESS);
  Wire.write(0xF3);
  if (Wire.endTransmission() != 0)
  {
    Serial.println("ERR 1");
    return 0.0;
  }
  delay(90);
  Wire.requestFrom(SHT_ADDRESS, 3);
  uint32_t start = millis();
  while (Wire.available() < 3)
  {
    if (millis() - start > 90)
    {
      Serial.println("ERR 2");
      return 0.0;
    }
    yield();
  }

  raw = Wire.read() << 8;
  raw += Wire.read();
  raw &= 0xFFFC;

  Serial.print("RAW TEM: ");
  Serial.println(raw, HEX);
  return -46.85 + (175.72 / 65536.0) * raw;
}


float getHumidity()
{
  uint16_t raw = 0;

  Wire.beginTransmission(SHT_ADDRESS);
  Wire.write(0xF5);
  if (Wire.endTransmission() != 0)
  {
    Serial.println("ERR 11");
    return 0.0;
  }
  delay(30);
  Wire.requestFrom(SHT_ADDRESS, 3);
  uint32_t start = millis();
  while (Wire.available() < 3)
  {
    if (millis() - start > 30)
    {
      Serial.println("ERR 12");
      return 0.0;
    }
    yield();
  }

  raw = Wire.read() << 8;
  raw += Wire.read();
  raw &= 0xFFFC;

  Serial.print("RAW HUM: ");
  Serial.println(raw, HEX);
  return -6.0 + (125.0 / 65536.0) * raw;
}


// -- END OF FILE --
