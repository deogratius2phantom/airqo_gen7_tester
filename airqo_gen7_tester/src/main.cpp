#include <Arduino.h>
#include <pin_definitions.h>
#include <configurations.h>
#define TINY_GSM_MODEM_SIM7600
#include <TinyGsmClient.h>
// put function declarations here:
#define GSM_SWITCH_PIN 54
TinyGsm        modem(Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115000);
  //clear_eeprom_configuration();
  initialize_pin_modes();
  if(initialize_sd()){
    load_sd_configuration();
  }
  else{
    //load_eeprom_configuration();
  }
  load_eeprom_configuration();
  scan_i2c();
  digitalWrite(GSM_SWITCH_PIN, HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(eeprom_configuration_file.DEVICE_NAME);
  // Serial.println(eeprom_configuration_file.DEVICE_WRITE_API_KEY);
  // Serial.println(eeprom_configuration_file.DEVICE_READ_API_KEY);
  // Serial.println(eeprom_configuration_file.DEVICE_CHANEL_ID);
  // Serial.println(eeprom_configuration_file.DEVICE_FIRMWARE_VERSION);
  // Serial.println(eeprom_configuration_file.DEVICE_UPLOAD_INTERVAL_MINUTES);
  // delay(5000);
  if(Serial.available()){
    while (Serial.available())
    {
      /* code */
      Serial1.write(Serial.read());
    }
  }
  if(Serial1.available()){
    while (Serial1.available())
    {
      /* code */
      Serial.write(Serial1.read());
    }
  } 
}

// put function definitions here:
