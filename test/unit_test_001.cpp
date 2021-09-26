//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-09-25
// PURPOSE: unit tests for the SHT21 temperature and humidity sensor
//          https://github.com/RobTillaart/SHT21
//          https://www.adafruit.com/product/2857
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)

/*
  most unit tests will test for fail 
  as there is no sensor connected
  and there is no mockup.
  
  It appears that Wire.write does not fail without sensor...
*/

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "SHT21.h"

int expect;  // TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;

unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_begin)
{
  SHT21 sht;

  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT21_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());
  Serial.println(sht.getRawTemperature());
  Serial.println(sht.getRawHumidity());

  // default value == 0
  assertEqual(-45, sht.getTemperature());
  assertEqual(0, sht.getHumidity());
  assertEqual(0, sht.getRawTemperature());
  assertEqual(0, sht.getRawHumidity());
}


unittest(test_read)
{
  SHT21 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.isConnected());
  expect = SHT21_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.read());
  expect = SHT21_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  start = millis();
  assertFalse(sht.read(false));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT21_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  start = millis();
  assertFalse(sht.read(true));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT21_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}


unittest(test_getStatus)
{
  SHT21 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertEqual(0xFFFF, sht.getStatus());
  expect = SHT21_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}


unittest(test_heater)
{
  SHT21 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertTrue(sht.heatOn());
  expect = SHT21_OK;
  assertEqual(expect, sht.getError());

  assertTrue(sht.heatOff());
  expect = SHT21_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.isHeaterOn());
  expect = SHT21_OK;
  assertEqual(expect, sht.getError());
}



unittest_main()

// --------