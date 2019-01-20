/**
 *   █████╗ ██████╗ ██████╗ ██╗   ██╗       ██████╗██╗     ██╗███╗   ███╗ █████╗ 
 *  ██╔══██╗██╔══██╗██╔══██╗██║   ██║      ██╔════╝██║     ██║████╗ ████║██╔══██╗
 *  ███████║██████╔╝██║  ██║██║   ██║█████╗██║     ██║     ██║██╔████╔██║███████║
 *  ██╔══██║██╔══██╗██║  ██║██║   ██║╚════╝██║     ██║     ██║██║╚██╔╝██║██╔══██║
 *  ██║  ██║██║  ██║██████╔╝╚██████╔╝      ╚██████╗███████╗██║██║ ╚═╝ ██║██║  ██║
 *  ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝        ╚═════╝╚══════╝╚═╝╚═╝     ╚═╝╚═╝  ╚═╝
 *      
 *  By Pablo Luaces <pablo.luaces@gmail.com>                              
 *  Licensed under Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
 *  Complete license text here: https://creativecommons.org/licenses/by-nc/4.0/
 *  [ Config file ]
 */

// Language
#define SYSTEM_LANG_ES // Selects language in lang.h, default english

// LCD
#define LCD_COLUMNS 16 // Number of LCD columns
#define LCD_ROWS 2 // Number of LCD rows
#define LCD_LIGHT 10 // LCD Backlight pin

// DHT Temperature / Humidity sensor
#define DHT_PIN A1 // DHT data pin
#define DHT_TYPE DHT11 // DHT11, DHT21 (AM2301), DHT22 (AM2302)
#define DHT_FAHRENHEIT false // True to output in Fahrenheit

// Remote control
#define REMOTE_PIN A2 // Remote receiver data pin

// System config
#define BUZZER_PIN 0 // Buzzer active speaker (don't upload sketch with it connected on pin 0-1)
#define TEMPERATURE_STEP 1 // Steps increasing/decreasing settings on menu
#define HUMIDITY_STEP 5 // Steps increasing/decreasing settings on menu
#define BACKLIGHT_TIMEOUT 60000 // 0 No timeout
#define DELAY_ON_BTN_PRESS 150 // Delay to prevent double trigger
#define FIRST_EEPROM_POS 1 // First EEPROM pos to write data (0 Reserved to flag)

// Relays
#define RELAY_OFF HIGH // 1 Not-active, 0 Active
#define RELAY_TEMP_DOWN 2
#define RELAY_TEMP_HIGH 3
#define RELAY_HUMI_DOWN 12
#define RELAY_HUMI_HIGH 13

// Keypad buttons identification
#define BTN_RIGHT  20
#define BTN_UP     21
#define BTN_DOWN   22
#define BTN_LEFT   23
#define BTN_SELECT 24
#define BTN_NONE   25

// Remote buttons identification
#define REMOTE_LE 0xFF22DD
#define REMOTE_RI 0xFFC23D
#define REMOTE_UP 0xFF629D
#define REMOTE_DO 0xFFA857
#define REMOTE_OK 0xFF02FD
#define REMOTE_00 0xFF4AB5
#define REMOTE_01 0xFF6897
#define REMOTE_02 0xFF9867
#define REMOTE_03 0xFFB04F
#define REMOTE_04 0xFF30CF
#define REMOTE_05 0xFF18E7
#define REMOTE_06 0xFF7A85
#define REMOTE_07 0xFF10EF
#define REMOTE_08 0xFF38C7
#define REMOTE_09 0xFF5AA5
#define REMOTE_AS 0xFF42BD
#define REMOTE_AL 0xFF52AD
#define REMOTE_RE 0xFFFFFFFF
