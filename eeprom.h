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
 *  [ Eeprom management file ]
 */

#include <EEPROM.h>

// Config data model
struct ArduClima {
    bool systemOn;
    bool soundOn;
    int temperature;
    int humidity;
    int tempMargin;
    int humiMargin;
};

// Data to store
ArduClima arduClimaSettings = {
    true,
    true,
    (DHT_FAHRENHEIT)? dht.convertCtoF(20):20,
    60,
    1,
    5
};

void writeParams(unsigned int pointer){ // Dinamic data alocation extends EEPROM life

    unsigned int dataSize = sizeof(arduClimaSettings);

    EEPROM.write(0, 1); // Data saved flag
    EEPROM.put(FIRST_EEPROM_POS, arduClimaSettings);
    
    lcd.clear();
    lcd.home();
    lcd.print(STR_CONFIG_SAVED);
    lcd.setCursor(0,1);
    lcd.print(String(dataSize) + "Bytes, Pos " + String(FIRST_EEPROM_POS));
    delay(1500);
}

void readParams(){
    if (EEPROM.read(0) == 1) EEPROM.get(FIRST_EEPROM_POS, arduClimaSettings); // Store in data model
}
