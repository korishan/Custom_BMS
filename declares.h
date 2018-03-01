#ifndef DECLARES_H
#define DECLARES_H
#include "U8glib.h"

// Display Prototypes
extern U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
void draw(void);

// Menu Prototypes
void PrintMenu();

// I2C Prototypes
void SearchDevices();
void writeTo(uint8_t deviceAddress, uint16_t settingFlag, uint16_t FlagValue);
int16_t readFrom(uint8_t deviceAddress, uint16_t settingFlag, uint16_t numBytes);

// BMS Prototypes
void readVoltages(uint8_t deviceAddress);

#endif

