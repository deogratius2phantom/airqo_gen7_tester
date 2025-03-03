#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

// Add your configuration settings here

// Example configuration settings
#include <Arduino.h>
#include <SD.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <pin_definitions.h>
const int WRITTEN_SIGNATURE = 0xBEEFDEED;
const int SIGNATURE_ADDRESS = 0;
typedef struct
{
    char DEVICE_NAME[32];
    char DEVICE_WRITE_API_KEY[32];
    char DEVICE_READ_API_KEY[32];
    char DEVICE_CHANEL_ID[32];
    char DEVICE_FIRMWARE_VERSION[32];
    int DEVICE_UPLOAD_INTERVAL_MINUTES;

} EEPROM_CONFIGURATION_FILE;
extern EEPROM_CONFIGURATION_FILE eeprom_configuration_file;
bool initialize_sd();
int load_sd_configuration();
void load_eeprom_configuration();
void clear_eeprom_configuration();
void initialize_pin_modes();
void scan_i2c();
#endif // CONFIGURATIONS_H