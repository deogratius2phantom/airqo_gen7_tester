#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H
// Define pin numbers for various sensors and modules
#define GSM_POWER_SWITCH_PIN                54
#define I2C_DEVICES_POWER_PIN               A8
#define RTC_POWER_PIN                       31
#define GPS_POWER_PIN                       A11
#define SD_CARD_POWER_PIN                   30
#define PM_SENSOR_POWER_PIN                 A2
#define PM_SENSOR_2_SOFTWARE_SERIAL_RX_PIN  12
#define PM_SENSOR_2_SOFTWARE_SERIAL_TX_PIN  13
#define POWER_SENSE_PIN                     29
#define SD_CS_PIN                           28


#define GSM_POWER_SWITCH_PIN    A0 //54 //A0
#define RX1_PIN                 D19 //45 //D19
#define TX1_PIN                 D18 //46 //D18
#define GSM_RESET_PIN           D10 //23 //D10

// gps related pins
#define GPS_POWER_SWITCH_PIN    A11 //86 //A11
#define RX2_PIN                 D17 // 12 //D17
#define TX2_PIN                 D16 // 13 //D16

//pms related pins
#define PMS_POWER_SWITCH_PIN    A2 // 95 //A2
#define PMS_RX3_PIN             D15 // 63 //D15
#define PMS_TX3_PIN             D14 // 64//D14
#define PMS_SSRX_PIN            D13 // 26 //D13
#define PMS_SSTX_PIN            D12 // 25//D12

//dht and sht related pins
#define DHT_SHT_POWER_SWITCH_PIN    A8 //89 //A8
#define DHT_DATA_PIN                A3 // 94 //A3
#define SHT_SDA_PIN                 D21 //43 //D21
#define SHT_SCL_PIN                 D20 //44 //D20

//sd card related pins
// #define PROBE_RX_PIN            PB3
// #define PROBE_TX_PIN            PA9
// #define SD_DETECT_PIN           PB12
#define SD_POWER_SWITCH_PIN     D30 // 60 //D30
#define SD_CS_PIN               D28 // 72 // D28
#define SD_MOSI_PIN             D51 // 21 //D51 
#define SD_MISO_PIN             D50 // 22 //D50
#define SD_SCK_PIN              D52 // 20 //D52

// Add more pin definitions as needed

#endif // PIN_DEFINITIONS_H