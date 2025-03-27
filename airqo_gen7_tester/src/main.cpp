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


// #define TINY_GSM_MODEM_SIM800

// #include <TinyGsmClient.h>
// #include <ArduinoHttpClient.h>

// #define SerialAT Serial1

// void sendToThingSpeak(String field1);

// // Define your APN credentials
// const char apn[]  = "TM";     // Replace with your APN
// const char user[] = "";             // APN username (if required)
// const char pass[] = "";             // APN password (if required)

// // ThingSpeak API
// const char server[] = "34.132.108.60";//"api.thingspeak.com";
// // const String apiKey = "";  // Your ThingSpeak API Key

// String imsi = "";

// void checkNetwork();
// String getIMSI();

// TinyGsm modem(SerialAT);
// TinyGsmClient client(modem);
// HttpClient http(client, server, 80);

// void setup() {
//     Serial.begin(115200);
//     pinMode(A0, OUTPUT);
//     digitalWrite(A0, HIGH);
//     SerialAT.begin(115200);

//     checkNetwork();
//     imsi = getIMSI();
//     Serial.print("IMSI: ");
//     Serial.println(imsi);

//     Serial.println("Initializing modem...");
//     if (!modem.restart()) {
//         Serial.println("Failed to restart modem!");
//         return;
//     }

//     Serial.println("Waiting for network...");
//     if (!modem.waitForNetwork()) {
//         Serial.println("Network connection failed!");
//         return;
//     }
//     Serial.println("Connected to network!");

//     Serial.println("Connecting to GPRS...");
//     if (!modem.gprsConnect(apn, user, pass)) {
//         Serial.println("Failed to connect to GPRS!");
//         return;
//     }
//     Serial.println("GPRS connected!");

//     sendToThingSpeak(imsi);  // Example: Send field1=25
// }

// void loop() {
//     // No loop logic required
// }


// void checkNetwork() {
//     Serial1.println("AT+CREG?");
//     delay(1000);
//     Serial1.println("AT+CGATT?");
//     delay(1000);
//   }

//   String getIMSI() {
//     Serial1.println("AT+CIMI");
//     delay(2000);
    
//     String response = "";
//     while (Serial1.available()) {
//         char c = Serial1.read();
//         if (c == '\n' || c == '\r') continue;
//         response += c;
//     }
    
//     response.trim();
    
//     String imsi = "";
//     for (char c : response) {
//       if (isDigit(c)) {
//         imsi += c;
//       }
//     }
    
//     return imsi;
//   }

// void sendToThingSpeak(String imsi) {
//     String url = "/device/234502106051372/selfconfig";//"/"+imsi+"/selfconfig";//"/update?api_key=" + apiKey + "&field1=" + String(field1);
    
//     Serial.print("Requesting URL: ");
//     Serial.println(url);
    
//     http.get(url);

//     int statusCode = http.responseStatusCode();
//     String response = http.responseBody();

//     Serial.print("Response Code: ");
//     Serial.println(statusCode);
//     Serial.print("Response Body: ");
//     Serial.println(response);

//     if (statusCode == 200) {
//         Serial.println("Data sent successfully!");
//     } else {
//         Serial.println("Failed to send data.");
//     }

//     modem.gprsDisconnect();
//     Serial.println("Disconnected from GPRS.");
// }