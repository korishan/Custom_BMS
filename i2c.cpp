#include <Arduino.h>
#include <Wire.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "constants.h"
#endif

#ifndef U8GLIB_H
#define U8GLIB_H
#include "U8glib.h"
#endif

#ifndef DECLARES_H
#define DECLARES_H
#include "declares.h"
#endif


void writeTo(uint8_t deviceAddress, uint16_t settingFlag, uint16_t FlagValue)
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(settingFlag);
  Wire.write(FlagValue);
  Wire.endTransmission();

  delay(10);
}

int16_t readFrom(uint8_t deviceAddress, uint16_t settingFlag, uint16_t numBytes)
{
  int numOfBytes;
  Wire.beginTransmission(deviceAddress);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, numBytes);

  int16_t rData = -1;
  numOfBytes = Wire.available();
  Serial.print("numOfBytes Available: ");
  Serial.println(numOfBytes);

  if (numOfBytes > 0) {
    for (int i = 0; i < numOfBytes; i++) {
      uint8_t aData = Wire.read();
      Serial.print("Value ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(aData);
      if (numBytes > 1) {
        uint8_t bData = Wire.read();
        rData = (aData << 8) | bData;
      }
      else {
        rData = aData;
      }
    }
    //    rData = Wire.read();
    //    if (numBytes > 1) {
    //      uint8_t b;
    //      b = Wire.read();
    //      rData = (rData << 8) | b;
    //      Serial.println("Second Byte");
  }

  return rData;
}

