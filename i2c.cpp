#include <Arduino.h>
#include <Wire.h>
#include "constants.h"
#include "U8glib.h"
#include "declares.h"
#include "bms.h"

short nDevices;

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

void SearchDevices()
{
  uint8_t findaddress;
  uint8_t error;

  Serial.println("\nScanning Bus...");

  int nDevices = 0;
  for (findaddress = 1; findaddress < 127; findaddress++ )
  {
    // The i2c_scanner uses the return value of the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(findaddress);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Found device at address 0x");
      if (findaddress < 16)
        Serial.print("0");
      Serial.print(findaddress, HEX);
      Serial.println("  !");
      bms.address = findaddress;
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (findaddress < 16)
        Serial.print("0");
      Serial.println(findaddress, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  return;
}


