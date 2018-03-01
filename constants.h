#ifndef CONSTANTS_H
#define CONSTANTS_H

const short SYS_STAT = 0x00;
const short CELLBAL1 = 0x01;
const short CELLBAL2 = 0x02;
const short CELLBAL3 = 0x03;
const short SYS_CTRL1 = 0x04;
const short SYS_CTRL2 = 0x05;
const short PROTECT1 = 0x06;
const short PROTECT2 = 0x07;
const short PROTECT3 = 0x08;
const short OV_TRIP = 0x09;
const short UV_TRIP = 0x0A;
const short CC_CFG = 0x0B;
const short VC_HI[] = {0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28};
const short VC_LO[] = {0x0D, 0x0F, 0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F, 0x21, 0x23, 0x25, 0x27, 0x29};
const short BAT_HI = 0x2A;
const short BAT_LO = 0x2B;
const short TS_HI[] = {0x2C, 0x2E};
const short TS_LO[] = {0x2D, 0x2F};
const short CC_HI = 0x32;
const short CC_LO = 0x33;
const short ADCGAIN1 = 0x50;
const short ADCOFFSET = 0x51;
const short ADCGAIN2 = 0x59;

// SYS_STAT
const short CC_READY = 7; // Couloum Counter Ready State. 1 = CC has new counter available
const short DEVICE_XREADY = 5; // 0 = Device OK, 1 = Internal Chip Fault Detected
const short OVRD_ALERT = 4; // ALERT pin
const short UV = 3; // Undervoltage Fault Detected
const short OV = 2; // Overvoltage Fault Detected
const short SCD = 1; // Short Circuit Fault Detected
const short OCD = 0; // Over Current Fault Detected

// SYS_CTRL1
const short LOAD_PRESENT = 7; // Valid when CHG_ON = 0, CHG pin detected & VLOAD_DETECT = 1
const short ADC_EN = 4; // ADC Enable/Disable Voltage/Temp readings (also OV Protection)
const short TEMP_SEL = 3; // 0 = Die Temp stored in TSx HI/LO, 1 = NTC stored in TSx HI/LO
const short SHUT_A = 1; // Shutdown A command from host sent in sequence below
const short SHUT_B = 0; // Shutdown B command from host sent in sequence below
// Shutdown sequence: A, B; A, B; A, B
//                    0, 0; 0, 1; 1, 0

// SYS_CTRL2
const short DELAY_DIS = 7; // Disable OV, UV, OCD, & SCD delays, approx 250ms
const short CC_EN = 6; // Coulomb Counter Continous Operation. 0 = Disable, 1 = Enabled (ONESHOT is ignored)
const short CC_ONESHOT = 5; // 1 = 1 shot reading of CC then turned back off
const short DSG_ON = 1; // Discharge FET driver/signal control
const short CHG_ON = 0; // Charge FET driver/signal control

// PROTECT1
const short RSNS = 7;
const short SCD_D1 = 4; // Short Circuit in Discharge Delay. 400uSec recommended only in systems
const short SCD_D0 = 3; // using maximum cell input resistance (Rc) of 1KOhm
const short SCD_T2 = 2; // Short Circuit in Discharge Threshold, bits 2 - 0
const short SCD_T1 = 1; // Short Circuit in Discharge Threshold, bits 2 - 0
const short SCD_T0 = 0; // Short Circuit in Discharge Threshold, bits 2 - 0

// PROTECT2
const short OCD_D2 = 6; //Overcurrent in Discharge Delay setting, bits 6 - 4
const short OCD_D1 = 5; //Overcurrent in Discharge Delay setting, bits 6 - 4
const short OCD_D0 = 4; //Overcurrent in Discharge Delay setting, bits 6 - 4
const short OCD_T3 = 3; //Overcurrent in Discharge Threshold setting, bits 3 - 0
const short OCD_T2 = 2; //Overcurrent in Discharge Threshold setting, bits 3 - 0
const short OCD_T1 = 1; //Overcurrent in Discharge Threshold setting, bits 3 - 0
const short OCD_T0 = 0; //Overcurrent in Discharge Threshold setting, bits 3 - 0

// PROTECT3
const short UV_D1 = 7; // Undervoltage Delay Setting, bits 7 - 6
const short UV_D0 = 6; // Undervoltage Delay Setting, bits 7 - 6
const short OV_D1 = 5; // Overvoltage Delay Setting, bits 5 - 4
const short OV_D0 = 4; // Overvoltage Delay Setting, bits 5 - 4

// OV_TRIP
const short OV_T7 = 7; // Middle 8 bits of the direct ADC mapping of the desired OV protection threshold,
const short OV_T6 = 6; // with upper 2 MSB set to 10 and lower 2 LSB set to 1000.
const short OV_T5 = 5; // The equivalent OV threshold is mapped to: 10-OV_T<7:0>1000.
const short OV_T4 = 4; //
const short OV_T3 = 3; // By default, OV_TRIP is configured to a 0xAC setting.
const short OV_T2 = 2; //
const short OV_T1 = 1; // Note that OV_TRIP is based on the ADC voltage, which requires back-calculation using the GAIN
const short OV_T0 = 0; // the GAIN and OFFSET values stored in ADCGAIN<4:0>and ADCOFFSET<7:0>.

// UV_TRIP
const short UV_T7 = 7; // Middle 8 bits of the direct ADC mapping of the desired UV protection threshold, with
const short UV_T6 = 6; // upper 2 MSB set to 01 and lower 4 LSB set to 0000. In other words,
const short UV_T5 = 5; // the equivalent OV threshold is mapped to: 01-UV_T<7:0>â€“0000.
const short UV_T4 = 4; //
const short UV_T3 = 3; // By default, UV_TRIP is configured to a 0x97 setting.
const short UV_T2 = 2; //
const short UV_T1 = 1; // Note that UV_TRIP is based on the ADC voltage, which requires back-calculation using the GAIN
const short UV_T0 = 0; // OFFSET values stored in ADCGAIN<4:0>and ADCOFFSET<7:0>.

// CC_CFG
const short CC_CFG5 = 5; //For optimal performance, these bits should be programmed to 0x19 upon device startup
const short CC_CFG4 = 4; // ^
const short CC_CFG3 = 3; // ^
const short CC_CFG2 = 2; // ^
const short CC_CFG1 = 1; // ^
const short CC_CFG0 = 0; // ^

// Cell Voltage Registers (Read Only)
// Two Byte Read
const short CV_D13 = 5; // D11:8 (Bits 3â€“0): Cell â€œxâ€� ADC reading, upper 6 MSB.
const short CV_D12 = 4; // Always returned as an atomic value if both high and low registers
const short CV_D11 = 3; // are read in the same transaction (using address auto-increment).
const short CV_D10 = 2; //
const short CV_D9 = 1; //
const short CV_D8 = 0; //
const short CV_D7 = 7; // D7:0 (Bits 7â€“0): Cell â€�xâ€� ADC reading, lower 8 LSB.
const short CV_D6 = 6; //
const short CV_D5 = 5; //
const short CV_D4 = 4; //
const short CV_D3 = 3; //
const short CV_D2 = 2; //
const short CV_D1 = 1; //
const short CV_D0 = 0; //

// BAT_HI/LO
// Two Byte Read
const short BAT_D15 = 7; // D15:8 (Bits 7â€“0): BAT calculation based on adding up Cells 1â€“15, upper 8 MSB.
const short BAT_D14 = 6; // Always returned as an atomic value if both high and low registers are
const short BAT_D13 = 5; // read in the same transaction (using address autoincrement)
const short BAT_D12 = 4; //
const short BAT_D11 = 3; //
const short BAT_D10 = 2; //
const short BAT_D9 = 1; //
const short BAT_D8 = 0; //
const short BAT_D7 = 7; // D7:0 (Bits 7â€“0): BAT calculation based on adding up Cells 1â€“15, lower 8 LSB
const short BAT_D6 = 6; //
const short BAT_D5 = 5; //
const short BAT_D4 = 4; //
const short BAT_D3 = 3; //
const short BAT_D2 = 2; //
const short BAT_D1 = 1; //
const short BAT_D0 = 0; //

// TS#_HI/LO
// Two Byte Read
const short TS_D13 = 5; // D11:8 (Bits 3â€“0): TS# (or DIETEMP; TS1 only) ADC reading, upper 6 MSB.
const short TS_D12 = 4; // Always returned as an atomic value if both high and
const short TS_D11 = 3; // low registers are read in the same transaction (using address auto-increment).
const short TS_D10 = 2; //
const short TS_D9 = 1; //
const short TS_D8 = 0; //
const short TS_D7 = 7; // D7:0 (Bits 7â€“0): TS# (or DIETEMP; TS1 only) ADC reading, lower 8 LSB
const short TS_D6 = 6; //
const short TS_D5 = 5; //
const short TS_D4 = 4; //
const short TS_D3 = 3; //
const short TS_D2 = 2; //
const short TS_D1 = 1; //
const short TS_D0 = 0; //

// CC_HI/LO
// Two Byte Read
const short CC15 = 7; // CC15:8 (Bits 7â€“0): Coulomb counter upper 8 MSB. Always returned as an atomic value if
const short CC14 = 6; // both high low registers are read in the same transaction (using address auto-increment).
const short CC13 = 5; //
const short CC12 = 4; //
const short CC11 = 3; //
const short CC10 = 2; //
const short CC9 = 1; //
const short CC8 = 0; //
const short CC7 = 7; // CC7:0 (Bits 7â€“0): Coulomb counter lower 8 LSB
const short CC6 = 6; //
const short CC5 = 5; //
const short CC4 = 4; //
const short CC3 = 3; //
const short CC2 = 2; //
const short CC1 = 1; //
const short CC0 = 0; //

// ADCGAIN1
const short ADCGAIN_4 = 3; // ADCGAIN4:3 (Bits 3â€“2, address 0x50):
const short ADCGAIN_3 = 2; // ADC GAIN
// offset upper 2 MSB
// ADCGAIN2
const short ADCGAIN_2 = 7; // ADCGAIN2:0 (Bits 7â€“5, address 0x59)
const short ADCGAIN_1 = 6; // ADC GAIN offset lower 3 LSB
const short ADCGAIN_0 = 5; // ADCGAIN<4:0> is a production-trimmed value for the ADC transfer function, in
// units of Î¼V/LSB. The range is 365 Î¼V/LSB to 396 Î¼V/LSB, in steps of 1 Î¼V/LSB,
// and may be calculated as follows:
// GAIN = 365 Î¼V/LSB + (ADCGAIN<4:0>in decimal) Ã— (1 Î¼V/LSB)
// Alternately, view the conversion table in the BQ769x0 PDF Page 45

// ADCOFFSET
const short ADCOFFSET7 = 7; // ADCOFFSET7:0 (Bits 7â€“0):
const short ADCOFFSET6 = 6; // ADC offset, stored in 2â€™s complement format in mV units. Positive full-scale range
const short ADCOFFSET5 = 5; // corresponds to 0x7F and negative full-scale corresponds to 0x80. The full-scale
const short ADCOFFSET4 = 4; // input range is â€“128 mV to 127 mV, with an LSB of 1 mV
const short ADCOFFSET3 = 3; //
const short ADCOFFSET2 = 2; // Review the table in the BQ769x0 PDF Page 45 for example offsets.
const short ADCOFFSET1 = 1; //
const short ADCOFFSET0 = 0; //

#endif
