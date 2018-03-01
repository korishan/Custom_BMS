#include <Wire.h>
#include "constants.h"
#include "declares.h"
#include "bms.h"

i2cBMS bms;

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  SearchDevices();
  PrintMenu();
//  draw();
}

void loop()
{
  oled_loop();
  
  uint8_t rData;
  //  readSerial();

  if (Serial.available())
  {
    char ch = Serial.read();
    switch (ch)
    {
      case '1':
        get_bms_status();
        break;
      case '2':
        //readVoltages(bms.address);
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


