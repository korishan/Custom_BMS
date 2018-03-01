#include <Wire.h>
#include "constants.h"
#include "declares.h"

short nDevices;

struct i2cBMS
{
  uint8_t address;
  uint8_t sys_stat;
  uint8_t cellbal1;
  uint8_t cellbal2;
  uint8_t cellbal3;
  uint8_t sys_ctrl1;
  uint8_t sys_ctrl2;
  uint8_t protect1;
  uint8_t protect2;
  uint8_t protect3;
  uint8_t ov_trip;
  uint8_t uv_trip;
  uint8_t cc_cfg;
  uint16_t vc_hi[15]; // For storing the HI values of up to 15 cells
  uint16_t vc_lo[15]; // For storing the LO values of up to 15 cells
  uint8_t bat_hi;
  uint8_t bat_lo;
  uint16_t ts_hi[3]; // For storing the HI values of up to 3 NTC's
  uint16_t ts_lo[3]; // For storing the LO values of up to 3 NTC's
  uint8_t cc_hi;
  uint8_t cc_lo;
  uint8_t adcgain1;
  uint8_t adcoffset;
  uint8_t adcgain2;
};

i2cBMS bms;

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  SearchDevices();
  PrintMenu();
  draw();
}

void loop()
{

  // picture loop
  oled.firstPage();
  do {
    draw();
  } while ( oled.nextPage() );

  uint8_t rData;
  //  readSerial();

  if (Serial.available())
  {
    char ch = Serial.read();
    switch (ch)
    {
      case '1':
        Serial.println("Getting Status from device...");
        //  rData = GetData(bms.address, SYS_STAT, 1);
        Serial.print("System Status: ");
        Serial.print(readFrom(bms.address, SYS_STAT, 1));
        Serial.println();
        break;
      case '2':
        readVoltages(bms.address);
        break;
      case '3':
        Serial.println("Not implimented yet.");
        break;
      case 'r':
        SearchDevices();
        break;
      default:
        Serial.println("Invalid option.");
        break;
    }
    delay(1000);
    Serial.println();
    Serial.println();
    PrintMenu();
  }
  delay(10000);           // wait 10 seconds for next scan
}

void PrintMenu()
{
  Serial.println("1: Device Status");
  Serial.println("2: Voltage Reading");
  Serial.println("3: ...");
  Serial.println("4: ...");
  Serial.println("r: ReScan for Devices");
}

void directCommand(char command)
{
  //
}

void readVoltages(uint8_t deviceAddress)
{
  for (int i = 0; i < 15; i++) {
    bms.vc_hi[i] = readFrom(deviceAddress, VC_HI[i], 2);
    bms.vc_lo[i] = readFrom(deviceAddress, VC_LO[i], 2);
  }
  Serial.print("VC_HI: ");
  for (int i = 0; i < 15; i++) {
    Serial.print(bms.vc_hi[i]);
    Serial.print(", ");
  }
  Serial.println();
  Serial.print("VC_LO: ");
  for (int i = 0; i < 15; i++) {
    Serial.print(bms.vc_lo[i]);
    Serial.print(", ");
  }
  Serial.println();
}

void SearchDevices()
{
  uint8_t findaddress;
  uint8_t error;

  Serial.println("\nScanning Bus...");

  nDevices = 0;
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


