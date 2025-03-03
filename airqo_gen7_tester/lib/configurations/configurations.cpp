#include "configurations.h"
#include <EEPROM.h>
EEPROM_CONFIGURATION_FILE eeprom_configuration_file;
// Add your configuration settings here
int load_sd_configuration() {
    Serial.println(F("Loading configuration from SD card..."));
    if (!SD.exists("config.txt")) {
        Serial.println(F("config.txt not found!"));
        Serial.println(F("Creating config.txt with default settings..."));
        File configFile = SD.open("config.txt", FILE_WRITE);
        if (configFile) {
            StaticJsonDocument<256> doc;
            doc["DEVICE_NAME"] = "AIQO_GXXX";
            doc["DEVICE_WRITE_API_KEY"] = "YOUR_WRITE_API_KEY";
            doc["DEVICE_READ_API_KEY"] = "YOUR_READ_API_KEY";
            doc["DEVICE_CHANEL_ID"] = "YOUR_CHANEL_ID";
            doc["DEVICE_FIRMWARE_VERSION"] = "123";
            doc["DEVICE_UPLOAD_INTERVAL_MINUTES"] = 30;
            serializeJsonPretty(doc, configFile);
            configFile.close();
            Serial.println(F("config.txt created with default settings."));
        } else {
            Serial.println(F("Failed to create config.txt!"));
        }
        return -1;
    }
    Serial.println(F("config.txt found!"));
    File configFile = SD.open("config.txt", FILE_READ);
    if (configFile) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, configFile);
        if (error) {
            Serial.println(F("Failed to read config.txt!"));
            return -1;
        }
        //serializeJsonPretty(doc, Serial); debug
        EEPROM.get(SIGNATURE_ADDRESS + sizeof(WRITTEN_SIGNATURE), eeprom_configuration_file);
        if (strcmp(doc["DEVICE_NAME"], "SMART_WATER_PROBE_X") == 0 &&
            strcmp(doc["DEVICE_WRITE_API_KEY"], "YOUR_WRITE_API_KEY") == 0 &&
            strcmp(doc["DEVICE_READ_API_KEY"], "YOUR_READ_API_KEY") == 0 &&
            strcmp(doc["DEVICE_CHANEL_ID"], "YOUR_CHANEL_ID") == 0 &&
            strcmp(doc["DEVICE_FIRMWARE_VERSION"], "123") == 0 &&
            doc["DEVICE_UPLOAD_INTERVAL_MINUTES"] == 30) {
            Serial.println(F("SD card contains default configuration values. PLEASE EDIT CONFIGURATION FILE!!!."));
            return -1;
        }
        if (strcmp(doc["DEVICE_NAME"], eeprom_configuration_file.DEVICE_NAME) != 0 ||
            strcmp(doc["DEVICE_WRITE_API_KEY"], eeprom_configuration_file.DEVICE_WRITE_API_KEY) != 0 ||
            strcmp(doc["DEVICE_READ_API_KEY"], eeprom_configuration_file.DEVICE_READ_API_KEY) != 0 ||
            strcmp(doc["DEVICE_CHANEL_ID"], eeprom_configuration_file.DEVICE_CHANEL_ID) != 0 ||
            strcmp(doc["DEVICE_FIRMWARE_VERSION"], eeprom_configuration_file.DEVICE_FIRMWARE_VERSION) != 0 ||
            doc["DEVICE_UPLOAD_INTERVAL_MINUTES"].as<int>() != eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES) {
            Serial.println(F("EEPROM data sync required."));
            Serial.println(F("The following configurations have been updated:"));
            if (strcmp(doc["DEVICE_NAME"], eeprom_configuration_file.DEVICE_NAME) != 0) {
                Serial.print(F("DEVICE_NAME: "));
                Serial.print(eeprom_configuration_file.DEVICE_NAME);
                Serial.print(F(" -> "));
                Serial.println(doc["DEVICE_NAME"].as<const char*>());
            }
            if (strcmp(doc["DEVICE_WRITE_API_KEY"], eeprom_configuration_file.DEVICE_WRITE_API_KEY) != 0) {
                Serial.print(F("DEVICE_WRITE_API_KEY: "));
                Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY);
                Serial.print(F(" -> "));
                Serial.println(doc["DEVICE_WRITE_API_KEY"].as<const char*>());
            }
            if (strcmp(doc["DEVICE_READ_API_KEY"], eeprom_configuration_file.DEVICE_READ_API_KEY) != 0) {
                Serial.print(F("DEVICE_READ_API_KEY: "));
                Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY);
                Serial.print(F(" -> "));
                Serial.println(doc["DEVICE_READ_API_KEY"].as<const char*>());
            }
            if (strcmp(doc["DEVICE_CHANEL_ID"], eeprom_configuration_file.DEVICE_CHANEL_ID) != 0) {
                Serial.print(F("DEVICE_CHANEL_ID: "));
                Serial.print(eeprom_configuration_file.DEVICE_CHANEL_ID);
                Serial.print(F(" -> "));
                Serial.println(doc["DEVICE_CHANEL_ID"].as<const char*>());
            }
            if (strcmp(doc["DEVICE_FIRMWARE_VERSION"], eeprom_configuration_file.DEVICE_FIRMWARE_VERSION) != 0) {
                Serial.print(F("DEVICE_FIRMWARE_VERSION: "));
                Serial.print(eeprom_configuration_file.DEVICE_FIRMWARE_VERSION);
                Serial.print(F(" -> "));
                Serial.println(doc["DEVICE_FIRMWARE_VERSION"].as<const char*>());
            }
            if (doc["DEVICE_UPLOAD_INTERVAL_MINUTES"].as<int>() != eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES) {
                Serial.print(F("DEVICE_UPLOAD_INTERVAL_MINUTES: "));
                Serial.print(eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES);
                Serial.print(F(" -> "));
                Serial.println(doc["DEVICE_UPLOAD_INTERVAL_MINUTES"].as<int>());
            }
            Serial.println(F("Updating EEPROM configuration..."));
            if (strcmp(doc["DEVICE_NAME"], eeprom_configuration_file.DEVICE_NAME) != 0) {
                strcpy(eeprom_configuration_file.DEVICE_NAME, doc["DEVICE_NAME"]);
            }
            if (strcmp(doc["DEVICE_WRITE_API_KEY"], eeprom_configuration_file.DEVICE_WRITE_API_KEY) != 0) {
                strcpy(eeprom_configuration_file.DEVICE_WRITE_API_KEY, doc["DEVICE_WRITE_API_KEY"]);
            }
            if (strcmp(doc["DEVICE_READ_API_KEY"], eeprom_configuration_file.DEVICE_READ_API_KEY) != 0) {
                strcpy(eeprom_configuration_file.DEVICE_READ_API_KEY, doc["DEVICE_READ_API_KEY"]);
            }
            if (strcmp(doc["DEVICE_CHANEL_ID"], eeprom_configuration_file.DEVICE_CHANEL_ID) != 0) {
                strcpy(eeprom_configuration_file.DEVICE_CHANEL_ID, doc["DEVICE_CHANEL_ID"]);
            }
            if (strcmp(doc["DEVICE_FIRMWARE_VERSION"], eeprom_configuration_file.DEVICE_FIRMWARE_VERSION) != 0) {
                strcpy(eeprom_configuration_file.DEVICE_FIRMWARE_VERSION, doc["DEVICE_FIRMWARE_VERSION"]);
            }
            if (doc["DEVICE_UPLOAD_INTERVAL_MINUTES"].as<int>() != eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES) {
                eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES = doc["DEVICE_UPLOAD_INTERVAL_MINUTES"];
            }

            // Show values that are still default
            if (strcmp(eeprom_configuration_file.DEVICE_NAME, "SMART_WATER_PROBE_X") == 0) {
                Serial.println(F("DEVICE_NAME is still default."));
            }
            if (strcmp(eeprom_configuration_file.DEVICE_WRITE_API_KEY, "YOUR_WRITE_API_KEY") == 0) {
                Serial.println(F("DEVICE_WRITE_API_KEY is still default."));
            }
            if (strcmp(eeprom_configuration_file.DEVICE_READ_API_KEY, "YOUR_READ_API_KEY") == 0) {
                Serial.println(F("DEVICE_READ_API_KEY is still default."));
            }
            if (strcmp(eeprom_configuration_file.DEVICE_CHANEL_ID, "YOUR_CHANEL_ID") == 0) {
                Serial.println(F("DEVICE_CHANEL_ID is still default."));
            }
            if (strcmp(eeprom_configuration_file.DEVICE_FIRMWARE_VERSION, "123") == 0) {
                Serial.println(F("DEVICE_FIRMWARE_VERSION is still default."));
            }
            if (eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES == 30) {
                Serial.println(F("DEVICE_UPLOAD_INTERVAL_MINUTES is still default."));
            }
            EEPROM.put(SIGNATURE_ADDRESS + sizeof(WRITTEN_SIGNATURE), eeprom_configuration_file);
            Serial.println(F("EEPROM configuration updated."));
        }
        configFile.close();
        return 0;
    }
    return 0;
}
void load_eeprom_configuration()
{
    int signature;
    EEPROM.get(SIGNATURE_ADDRESS, signature);
    if(signature == WRITTEN_SIGNATURE) {
        EEPROM.get(SIGNATURE_ADDRESS + sizeof(signature), eeprom_configuration_file);
        Serial.println(F("EEPROM configuration loaded successfully!"));
        Serial.print(F("DEVICE_NAME: "));
        Serial.println(eeprom_configuration_file.DEVICE_NAME);
        if (strcmp(eeprom_configuration_file.DEVICE_WRITE_API_KEY, "YOUR_WRITE_API_KEY") != 0) {
            Serial.print(F("DEVICE_WRITE_API_KEY: "));
            Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY[0]);
            Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY[1]);
            Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY[2]);
            for (int i = 3; i < strlen(eeprom_configuration_file.DEVICE_WRITE_API_KEY) - 3; i++) {
                Serial.print('*');
            }
            Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY[strlen(eeprom_configuration_file.DEVICE_WRITE_API_KEY) - 3]);
            Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY[strlen(eeprom_configuration_file.DEVICE_WRITE_API_KEY) - 2]);
            Serial.print(eeprom_configuration_file.DEVICE_WRITE_API_KEY[strlen(eeprom_configuration_file.DEVICE_WRITE_API_KEY) - 1]);
            Serial.println();
        } else {
            Serial.println(F("DEVICE_WRITE_API_KEY:"));
            Serial.println(eeprom_configuration_file.DEVICE_WRITE_API_KEY);
        }
        if (strcmp(eeprom_configuration_file.DEVICE_READ_API_KEY, "YOUR_READ_API_KEY") != 0) {
            Serial.print(F("DEVICE_READ_API_KEY: "));
            Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY[0]);
            Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY[1]);
            Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY[2]);
            for (int i = 3; i < strlen(eeprom_configuration_file.DEVICE_READ_API_KEY) - 3; i++) {
                Serial.print('*');
            }
            Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY[strlen(eeprom_configuration_file.DEVICE_READ_API_KEY) - 3]);
            Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY[strlen(eeprom_configuration_file.DEVICE_READ_API_KEY) - 2]);
            Serial.print(eeprom_configuration_file.DEVICE_READ_API_KEY[strlen(eeprom_configuration_file.DEVICE_READ_API_KEY) - 1]);
            Serial.println();
        } else {
            Serial.println(F("DEVICE_READ_API_KEY:"));
            Serial.println(eeprom_configuration_file.DEVICE_READ_API_KEY);
        }
        Serial.print(F("DEVICE_CHANEL_ID: "));
        Serial.println(eeprom_configuration_file.DEVICE_CHANEL_ID);
        Serial.print(F("DEVICE_FIRMWARE_VERSION: "));
        Serial.println(eeprom_configuration_file.DEVICE_FIRMWARE_VERSION);
        Serial.print(F("DEVICE_UPLOAD_INTERVAL_MINUTES: "));
        Serial.println(eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES);

        // Check which values are still default
        if (strcmp(eeprom_configuration_file.DEVICE_NAME, "SMART_WATER_PROBE_X") == 0) {
            Serial.println(F("DEVICE_NAME is still default."));
        }
        if (strcmp(eeprom_configuration_file.DEVICE_WRITE_API_KEY, "YOUR_WRITE_API_KEY") == 0) {
            Serial.println(F("DEVICE_WRITE_API_KEY is still default."));
        }
        if (strcmp(eeprom_configuration_file.DEVICE_READ_API_KEY, "YOUR_READ_API_KEY") == 0) {
            Serial.println(F("DEVICE_READ_API_KEY is still default."));
        }
        if (strcmp(eeprom_configuration_file.DEVICE_CHANEL_ID, "YOUR_CHANEL_ID") == 0) {
            Serial.println(F("DEVICE_CHANEL_ID is still default."));
        }
        if (strcmp(eeprom_configuration_file.DEVICE_FIRMWARE_VERSION, "123") == 0) {
            Serial.println(F("DEVICE_FIRMWARE_VERSION is still default."));
        }
        if (eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES == 30) {
            Serial.println(F("DEVICE_UPLOAD_INTERVAL_MINUTES is still default."));
        }
    }
    else {
        Serial.println(F("EEPROM configuration not found!"));
        Serial.println(F("Writing default configuration to EEPROM..."));
        EEPROM.put(SIGNATURE_ADDRESS, WRITTEN_SIGNATURE);
        EEPROM.put(SIGNATURE_ADDRESS + sizeof(signature), eeprom_configuration_file);
        Serial.println(F("Default configuration written to EEPROM!"));
    }
}
bool initialize_sd() {
    Serial.println(F("Initializing SD card..."));
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println(F("SD card initialization failed!"));
        return false;
    }
    Serial.println(F("SD card initialized successfully!"));
    return true;
}
void clear_eeprom_configuration() {
    Serial.println(F("Clearing EEPROM configuration..."));
    EEPROM.put(SIGNATURE_ADDRESS, 0);
    EEPROM.put(SIGNATURE_ADDRESS + sizeof(WRITTEN_SIGNATURE), eeprom_configuration_file);
    for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
    Serial.println(F("EEPROM configuration cleared!"));
}
void initialize_pin_modes()
{
    pinMode(GSM_POWER_SWITCH_PIN, OUTPUT);
    pinMode(I2C_DEVICES_POWER_PIN, OUTPUT);
    pinMode(RTC_POWER_PIN, OUTPUT);
    pinMode(GPS_POWER_PIN, OUTPUT);
    pinMode(SD_CARD_POWER_PIN, OUTPUT);
    pinMode(PM_SENSOR_POWER_PIN, OUTPUT);
    pinMode(POWER_SENSE_PIN, INPUT);
    pinMode(SD_CS_PIN, INPUT);

    digitalWrite(RTC_POWER_PIN, HIGH);
    digitalWrite(I2C_DEVICES_POWER_PIN, HIGH);
}
void scan_i2c() {
    Wire.begin();
    Serial.println(F("Scanning I2C bus..."));
    byte error, address;
    int nDevices = 0;

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print(F("I2C device found at address 0x"));
            if (address < 16) {
                Serial.print(F("0"));
            }
            Serial.print(address, HEX);
            Serial.println(F(" !"));

            nDevices++;
        } else if (error == 4) {
            Serial.print(F("Unknown error at address 0x"));
            if (address < 16) {
                Serial.print(F("0"));
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println(F("No I2C devices found."));
    } else {
        Serial.println(F("I2C scan complete."));
    }
}