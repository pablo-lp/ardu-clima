/**
 *     █████╗ ██████╗ ██████╗ ██╗   ██╗       ██████╗██╗     ██╗███╗   ███╗ █████╗ 
 *    ██╔══██╗██╔══██╗██╔══██╗██║   ██║      ██╔════╝██║     ██║████╗ ████║██╔══██╗
 *    ███████║██████╔╝██║  ██║██║   ██║█████╗██║     ██║     ██║██╔████╔██║███████║
 *    ██╔══██║██╔══██╗██║  ██║██║   ██║╚════╝██║     ██║     ██║██║╚██╔╝██║██╔══██║
 *    ██║  ██║██║  ██║██████╔╝╚██████╔╝      ╚██████╗███████╗██║██║ ╚═╝ ██║██║  ██║
 *    ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝        ╚═════╝╚══════╝╚═╝╚═╝     ╚═╝╚═╝  ╚═╝
 *                                                                                 
 *  
 *  By Pablo Luaces <pablo.luaces@gmail.com>                                       
 *  Licensed under Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
 *  Complete license text here: https://creativecommons.org/licenses/by-nc/4.0/
 *  Version: 1.0
 *  [ Main file ]
 */

#include <MenuSystem.h>
#include <Thread.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#include <DHT.h>

#include "config.h" // Settings constants definitions

Thread defaultTimer; // Update time and display at x interval
Thread tempTimer; // Update temperature at x interval
Thread relayTimer; // Update relays state at x interval
LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7); // Init LCD
IRrecv remote(REMOTE_PIN); // IR Receiver instance for remote (pin 3)
DHT dht(DHT_PIN, DHT_TYPE); // DHT Sensor (pin 2)

#include "lang.h" // Language constants definitions
#include "eeprom.h" // Permanent save settings methods
#include "core.h" // Main methods

void setup() {
    //Serial.begin(115200);   // Inicializar puerto serie
    lcd.begin(LCD_COLUMNS, LCD_ROWS);   // Inicializar el LCD
    lcd.createChar(0, simboloLogo);
    if (DHT_FAHRENHEIT) lcd.createChar(1, simboloFahrenheit);
    else lcd.createChar(1, simboloGrados);
    lcd.createChar(2, simboloHumedad);
    lcd.createChar(3, simboloOver);
    lcd.createChar(4, simboloUnder);
    lcd.createChar(5, simboloEqual);
    lcd.home();
    
    lcd.print("ARDU-CLIMA 2019");
    lcd.setCursor(0,1);
    lcd.print("By Pablo Luaces");
    
    delay(1000);

    readParams(); // Read EEPROM settings
    createMenu(); // Create menu in memory
    initGpio(); // Configure Arduino Pinout

    defaultTimer.onRun(updateLCD); // LCD Update
    defaultTimer.setInterval(100);
    
    tempTimer.onRun(updateSensorData); // Get sensor data
    tempTimer.setInterval(1000);

    relayTimer.onRun(controlRelays); // Control the relays
    relayTimer.setInterval(10000);
}

void loop() {
    manageBacklight(); // Auto power off backlight
    if(defaultTimer.shouldRun()) defaultTimer.run();
    if(tempTimer.shouldRun()) tempTimer.run();
    if(relayTimer.shouldRun()) relayTimer.run();
}
