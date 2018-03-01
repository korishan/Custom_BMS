#include <Wire.h>
#include "Arduino.h"
#include "constants.h"
#include "declares.h"
#include "bms.h"

void get_bms_status()
{
  Serial.println("Getting Status from device...");
  Serial.print("System Status: ");
  Serial.print(readFrom(bms.address, SYS_STAT, 1));
  Serial.println();
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

void bmsStatus(uint16_t statusMode, uint8_t value)
{
  switch (statusMode)
  {
    case SYS_STAT:
    
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
    case VC_HI:
      break;
    case VC_LO:
      break;
    case BAT_HI:
      break;
    case BAT_LO:
      break;
    case TS_HI:
      break;
    case TS_LO:
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
    default:
      // Invalid Status Option
      break;

  }
}

