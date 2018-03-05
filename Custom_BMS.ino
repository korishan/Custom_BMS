#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "constants.h"
#include "declares.h"
#include "bms.h"
#include "globals.h"
#include "display.h"

const byte numChars = 32;
boolean newData;

long displayStatusRefresh;
long bmsRefresh;
uint8_t oledDisplay;

extern SSD1306AsciiWire oled;

i2cBMS bms;

void setup()
{
  Wire.begin();
  Wire.setClock(400000L);

  Serial.begin(115200);
  setupDisplay();
  setDefaults();

  SearchDevices();
  PrintMenu();
  //  draw();
}

void loop()
{
  uint8_t rData;
  static long previousTimer;
  static uint8_t currentDisplay;
  unsigned long currentTimer = millis();

  if (currentTimer - previousTimer > bmsRefresh)
  {
    previousTimer = currentTimer;
    get_bms_details();
  }
  readSerial();
  oled_loop();

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

void readSerial()
{
  char strCmd[32];
  char receivedChars[numChars]; // an array to store the received data
  char strRemaining[32];
  int intValue = 0;
  char strVariable[16];

  recvWithEndMarker(receivedChars);
  if (newData == true)
  {
    Serial.print("Received Command: ");
    Serial.println(receivedChars);
    sscanf(receivedChars, "%s", strCmd);

    switch (strCmd[0])
    {
      case '1':
        oledDisplay = DISPLAYMENU;
        get_bms_status();
        break;
      case '2':
        oledDisplay = DISPLAYVOLTAGES;
        //get_bms_voltages(bms.address);
        break;
      case '3':
        Serial.println("Not implimented yet.");
        break;
      case 'r':
        oled.clear();
        oled.println("ReScanning I2C Bus");
        SearchDevices();
        oled.println("Completed Scan");
        break;
      case 'd':
        switch (strCmd[1])
        {
          case 'v':
            if (strcmp(receivedChars, "dv disp") == 0)
              Serial.println(displayStatusRefresh);
            else if (strcmp(receivedChars, "dv bms") == 0)
              Serial.println(bmsRefresh);
            else if (receivedChars[2] == 1) {
              Serial.print(".");
              Serial.println(newData);
            }
            break;
        }
        break;
      case 's':
        char buf[64];
        sscanf(receivedChars, "%s %s %d", strCmd, strVariable, &intValue);
        switch (strCmd[1])
        {
          case 'v':
            sprintf(buf, "Current Value of 'displayStatusRefresh' = %d", displayStatusRefresh);
            Serial.println(buf);
            sprintf(buf, "Trying to set 'displayStatusRefresh' to %d", intValue);
            Serial.println(buf);
            sprintf(buf, "Value of 'strVariable' is %s", strVariable);
            Serial.println(buf);

            if (strVariable == "disp")
              displayStatusRefresh = intValue;
            sprintf(buf, "New Value of 'displayStatusRefresh' = %d", displayStatusRefresh);
            Serial.println(buf);

            break;
          default:
            break;
        }
        if (receivedChars == "")
        {

        }
        else if (receivedChars == "")
        {

        }
        break;
      default:
        Serial.println("Invalid option.");
    }
    newData = false;

    Serial.println();
    Serial.println();
    PrintMenu();
  }
}

boolean recvWithEndMarker(char *rcvdChars) {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();

    if (rc != endMarker) {
      rcvdChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      rcvdChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void setDefaults()
{
  displayStatusRefresh = 5000;
  bmsRefresh = 1000;
  oledDisplay = DISPLAYSTATUS;
}

int getValue(char *str)
{
  uint8_t res = 0;
  char buf[strlen(str)];

  for (uint8_t i = strlen(str) - 1; str[i] != ' '; i--)
    buf[i] = str[i];

  return atoi(buf);
}

