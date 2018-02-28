#include <Wire.h>
#include "U8glib.h"
#include "constants.h"

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI

short nDevices;

struct i2cBMS
{
  byte address;
  byte sys_stat;
  byte cellbal1;
  byte cellbal2;
  byte cellbal3;
  byte sys_ctrl1;
  byte sys_ctrl2;
  byte protect1;
  byte protect2;
  byte protect3;
  byte ov_trip;
  byte uv_trip;
  byte cc_cfg;
  uint16_t vc_hi[15]; // For storing the HI values of up to 15 cells
  uint16_t vc_lo[15]; // For storing the LO values of up to 15 cells
  byte bat_hi;
  byte bat_lo;
  uint16_t ts_hi[3]; // For storing the HI values of up to 3 NTC's
  uint16_t ts_lo[3]; // For storing the LO values of up to 3 NTC's
  byte cc_hi;
  byte cc_lo;
  byte adcgain1;
  byte adcoffset;
  byte adcgain2;
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

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here
  oled.setFont(u8g_font_unifont);
  oled.drawStr( 0, 20, "Hello World!");
}

void loop()
{

  // picture loop
  oled.firstPage();
  do {
    draw();
  } while ( oled.nextPage() );

  byte rData;
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

void writeTo(byte deviceAddress, uint16_t settingFlag, uint16_t FlagValue)
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(settingFlag);
  Wire.write(FlagValue);
  Wire.endTransmission();

  delay(10);
}

int16_t readFrom(byte deviceAddress, uint16_t settingFlag, uint16_t numBytes)
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
      byte aData = Wire.read();
      Serial.print("Value ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(aData);
      if (numBytes > 1) {
        byte bData = Wire.read();
        rData = (aData << 8) | bData;
      }
      else {
        rData = aData;
      }
    }
    //    rData = Wire.read();
    //    if (numBytes > 1) {
    //      byte b;
    //      b = Wire.read();
    //      rData = (rData << 8) | b;
    //      Serial.println("Second Byte");
  }

  return rData;
}

void readVoltages(byte deviceAddress)
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
  byte findaddress;
  byte error;

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

