#include <Wire.h>
#include "Arduino.h"
#include "constants.h"
#include "declares.h"
#include "bms.h"

void get_bms_details()
{
  get_bms_status();
  get_bms_voltages(bms.address);
  
}

void get_bms_status()
{
  get_Data(bms.address, SYS_STAT);
  return;
}

void get_bms_voltages(uint8_t deviceAddress)
{
  
  for (int i = 0; i < 4; i++) {
    bms.vc_hi[i] = readFrom(deviceAddress, VC_HI[i], 1);
    bms.vc_lo[i] = readFrom(deviceAddress, VC_LO[i], 1);
  }
}

void get_Data(uint8_t deviceAddress, uint16_t statusMode)
{
  uint16_t rData;

  switch (statusMode)
  {
    case SYS_STAT:
      rData = readFrom(deviceAddress, statusMode, 1);
      bms.sys_stat = rData;
      break;
    case CELLBAL1:
      break;
    case CELLBAL2:
      break;
    case CELLBAL3:
      break;
    case SYS_CTRL1:
      break;
    case SYS_CTRL2:
      break;
    case PROTECT1:
      break;
    case PROTECT2:
      break;
    case PROTECT3:
      break;
    case OV_TRIP:
      break;
    case UV_TRIP:
      break;
    case CC_CFG:
      break;
    case VC_VOLT:
      break;
    case BATTERY:
      break;
    case TS:
      break;
    case CC_HI:
      break;
    case CC_LO:
      break;
    case ADCGAIN1:
      break;
    case ADCOFFSET:
      break;
    case ADCGAIN2:
      break;
    default:
      // Invalid Status Option
      break;
  }
  return;
}

void displayData(uint8_t deviceAddress, uint16_t statusMode)
{
  char *buf = malloc(sizeof (char) * 100);
  String sbuf[8];
  uint16_t rData;

  switch (statusMode)
  {
    case SYS_STAT:
      rData = bms.sys_stat;
      if (rData & CC_READY) sbuf[0] = String("CC Read");
      sbuf[1][0] = " "; // This bit isn't used
      if (rData & DEVICE_XREADY) sbuf[2] = String(" ");
      if (rData & OVRD_ALERT) sbuf[3] = String("ALERT");
      if (rData & UV) sbuf[4] =  String("UnderVolt");
      if (rData & OV) sbuf[5] =  String("OverVolt");
      if (rData & SCD) sbuf[6] = String("ShortCircuit");
      if (rData & OCD) sbuf[7] = String("OverCurrent");
      Serial.print("System Status: ");
      for (int i = 0; i < 8; i++)
      {
        Serial.print(sbuf[i]);
        Serial.print(" | ");
      }
      Serial.println();
      
      break;
    case CELLBAL1:
      break;
    case CELLBAL2:
      break;
    case CELLBAL3:
      break;
    case SYS_CTRL1:
      break;
    case SYS_CTRL2:
      break;
    case PROTECT1:
      break;
    case PROTECT2:
      break;
    case PROTECT3:
      break;
    case OV_TRIP:
      break;
    case UV_TRIP:
      break;
    case CC_CFG:
      break;
    case VC_VOLT:
      break;
    case BATTERY:
      break;
    case TS:
      break;
    case CC_HI:
      break;
    case CC_LO:
      break;
    case ADCGAIN1:
      break;
    case ADCOFFSET:
      break;
    case ADCGAIN2:
      break;
    default:
      // Invalid Status Option
      break;
  }
  free( buf);
  return;
 
}

