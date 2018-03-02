
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
  int16_t vc_hi[15]; // For storing the HI values of up to 15 cells
  int16_t vc_lo[15]; // For storing the LO values of up to 15 cells
  uint8_t bat_hi;
  uint8_t bat_lo;
  int16_t ts_hi[3]; // For storing the HI values of up to 3 NTC's
  int16_t ts_lo[3]; // For storing the LO values of up to 3 NTC's
  uint8_t cc_hi;
  uint8_t cc_lo;
  uint8_t adcgain1;
  uint8_t adcoffset;
  uint8_t adcgain2;
};

extern i2cBMS bms;
