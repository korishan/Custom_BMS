#ifndef DECLARES_H
#define DECLARES_H

// Display Prototypes
void setupDisplay();
void draw(void);
void oled_loop();
void printScreen(uint8_t x, uint8_t y, String buf);
void displayStatus();
void displaySysStatus();
void displayVoltage();
void displayMenu();

// Menu Prototypes
void PrintMenu();

// I2C Prototypes
void SearchDevices();
void writeTo(uint8_t deviceAddress, uint16_t settingFlag, uint16_t FlagValue);
int16_t readFrom(uint8_t deviceAddress, uint16_t settingFlag, uint16_t numBytes);

// BMS Prototypes
void get_bms_voltages(uint8_t deviceAddress);
void get_bms_status();
void get_Data(uint8_t deviceAddress, uint16_t statusMode);
char* parseData(uint16_t statusMode, uint8_t value);
void get_bms_details();

#endif

