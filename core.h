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
 *  [ Core file ]
 */

// Core vars

int temperature = 0;
int humidity = 0;
bool menuActive = false;
unsigned long backlightStartTime = 0;
uint8_t lastRemoteBtn = BTN_NONE;
decode_results results;
char buffer[16];

byte simboloLogo[] = { 0x00, 0x04, 0x0E, 0x17, 0x0A, 0x04, 0x00, 0x00 };
byte simboloGrados[] = { 0x18, 0x18, 0x00, 0x0F, 0x08, 0x08, 0x0F, 0x00 };
byte simboloFahrenheit[] = { 0x18, 0x18, 0x00, 0x0F, 0x08, 0x0E, 0x08, 0x08 };
byte simboloHumedad[] = { 0x0A, 0x0A, 0x12, 0x14, 0x05, 0x09, 0x0A, 0x0A };
byte simboloOver[] = { 0x1B, 0x11, 0x00, 0x0A, 0x1B, 0x1B, 0x1B, 0x1B };
byte simboloUnder[] = { 0x1B, 0x1B, 0x1B, 0x1B, 0x0A, 0x00, 0x11, 0x1B };
byte simboloEqual[] = { 0x1E, 0x1D, 0x1D, 0x1D, 0x1D, 0x05, 0x11, 0x19 };

// Core methods

void backlightOn(){
    backlightStartTime = millis();
    digitalWrite(10, HIGH); // Backlight on
}

void manageBacklight(){
    if (BACKLIGHT_TIMEOUT > 0 && backlightStartTime > 0){
        long millis_elapsed = millis() - backlightStartTime;
        if (millis_elapsed > BACKLIGHT_TIMEOUT){
            digitalWrite(10, LOW); // Backlight off
            backlightStartTime = 0;
        }
    }
}

void buzzer(unsigned int steps, unsigned int duration){
    if (arduClimaSettings.soundOn){
        for(unsigned int i = 0; i < steps; i++){
            digitalWrite(BUZZER_PIN, LOW);
            delay(duration);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(100);
        }
    }
}

int irRemoteAction(unsigned long irValue){
    switch (irValue) {
        case REMOTE_UP: // Up pressed
            return BTN_UP;
        case REMOTE_DO: // Down pressed
            return BTN_DOWN;
        case REMOTE_RI: // Right pressed
            return BTN_RIGHT; 
        case REMOTE_LE: // Left pressed
            return BTN_LEFT;
        case REMOTE_OK: // Ok presed
            return BTN_SELECT;
        case REMOTE_00: // 0 presed
            return 0;
        case REMOTE_01: // 1 presed
            return 1;
        case REMOTE_02: // 2 presed
            return 2;
        case REMOTE_03: // 3 presed
            return 3;
        case REMOTE_04: // 4 presed
            return 4;
        case REMOTE_05: // 5 presed
            return 5;
        case REMOTE_06: // 6 presed
            return 6;
        case REMOTE_07: // 7 presed
            return 7;
        case REMOTE_08: // 8 presed
            return 8;
        case REMOTE_09: // 9 presed
            return 9;
        case REMOTE_RE: // Long press
            return lastRemoteBtn;
        default:
            return BTN_NONE;
    }
}

int read_inputs(){

    if (remote.decode(&results)) { // Remote input

        uint8_t raction = irRemoteAction(results.value); // Get action
        lastRemoteBtn = raction; // Save last key press to repeat
        // Serial.print("Remote: ");
        // Serial.println(results.value, HEX); // Print remote value
        remote.resume(); // Next value
        return raction; // Return action
        
    }else{ // Keypad input
      
        unsigned int adc_key_in = analogRead(0);
        // Serial.print("Key: ");
        // Serial.println(adc_key_in); // Print keypad key value
        if (adc_key_in < 50)   return BTN_RIGHT; 
        if (adc_key_in < 250)  return BTN_UP;
        if (adc_key_in < 400)  return BTN_DOWN;
        if (adc_key_in < 650)  return BTN_LEFT;
        if (adc_key_in < 850)  return BTN_SELECT; 
    }

    return BTN_NONE;
}

void defaultScreen(){
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.print("ARDU-CLIMA");
    
    sprintf(buffer, " %3d", temperature);
    lcd.print(buffer);
    lcd.write(byte(1));

    lcd.setCursor(0,1);

    if (!arduClimaSettings.systemOn) lcd.print("--- OFF ---  ");
    else{
        lcd.print("TEMP ");
        if (temperature > arduClimaSettings.temperature + arduClimaSettings.tempMargin) lcd.write(byte(3));
        else if (temperature < arduClimaSettings.temperature - arduClimaSettings.tempMargin) lcd.write(byte(4));
        else lcd.write(byte(5));
        lcd.print(" HUM ");
        if (humidity > arduClimaSettings.humidity + arduClimaSettings.humiMargin) lcd.write(byte(3));
        else if (humidity < arduClimaSettings.humidity - arduClimaSettings.humiMargin) lcd.write(byte(4));
        else lcd.write(byte(5));
    }

    lcd.setCursor(12,1);
    sprintf(buffer, "%3d", humidity);
    lcd.print(buffer);
    lcd.write(byte(2));
}

void relaysShutdown(){
    digitalWrite(RELAY_TEMP_DOWN, RELAY_OFF);
    digitalWrite(RELAY_TEMP_HIGH, RELAY_OFF);
    digitalWrite(RELAY_HUMI_DOWN, RELAY_OFF);
    digitalWrite(RELAY_HUMI_HIGH, RELAY_OFF);
}

void initGpio(){
    pinMode(LCD_LIGHT, OUTPUT); // Backlight pin
    backlightOn(); // Backlight on
    remote.enableIRIn(); // Starts the IR receiver

    // Init the buzzer
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH);

    // Init the relays pins
    pinMode(RELAY_TEMP_DOWN, OUTPUT);
    pinMode(RELAY_TEMP_HIGH, OUTPUT);
    pinMode(RELAY_HUMI_DOWN, OUTPUT);
    pinMode(RELAY_HUMI_HIGH, OUTPUT);

    // Set relays off
    relaysShutdown();
}

#include "menu.h" // Menu methods

void mainScreenInputs(){
    switch (read_inputs()) {
        case BTN_UP: // Previous item
            ms.prev();
            displayMenu();
            buzzer(1, 20);
            break;
        case BTN_DOWN: // Next item
            ms.next();
            displayMenu();
            buzzer(1, 20);
            break;
        case BTN_RIGHT: // Right pressed
        case BTN_LEFT: // Left pressed
            backlightOn();
            break;
        case BTN_SELECT: // Select presed
            backlightOn();
            if (menuActive)
            ms.select();
    }
}

void updateLCD() { // Runs every 200ms
    mainScreenInputs(); // Handle inputs
    if (!menuActive) defaultScreen();
}

void updateSensorData(){ // Runs every second
    int temp = dht.readTemperature(DHT_FAHRENHEIT);
    int humi = dht.readHumidity();
    if (!isnan(temp)) temperature = temp;
    if (!isnan(humi)) humidity = humi;
}

void controlRelays(){
    
    if (arduClimaSettings.systemOn){
      
        // Temperature
        if (temperature > arduClimaSettings.temperature + arduClimaSettings.tempMargin){
            digitalWrite(RELAY_TEMP_DOWN, RELAY_OFF);
            digitalWrite(RELAY_TEMP_HIGH, !RELAY_OFF);
        }else if (temperature < arduClimaSettings.temperature - arduClimaSettings.tempMargin){
            digitalWrite(RELAY_TEMP_DOWN, !RELAY_OFF);
            digitalWrite(RELAY_TEMP_HIGH, RELAY_OFF);   
        }else{
            digitalWrite(RELAY_TEMP_DOWN, RELAY_OFF);
            digitalWrite(RELAY_TEMP_HIGH, RELAY_OFF);   
        }
    
        // Humidity
        if (humidity > arduClimaSettings.humidity + arduClimaSettings.humiMargin){
            digitalWrite(RELAY_HUMI_DOWN, RELAY_OFF);
            digitalWrite(RELAY_HUMI_HIGH, !RELAY_OFF);
        }else if (humidity < arduClimaSettings.humidity - arduClimaSettings.humiMargin){
            digitalWrite(RELAY_HUMI_DOWN, !RELAY_OFF);
            digitalWrite(RELAY_HUMI_HIGH, RELAY_OFF);   
        }else{
            digitalWrite(RELAY_HUMI_DOWN, RELAY_OFF);
            digitalWrite(RELAY_HUMI_HIGH, RELAY_OFF);   
        }
        
    }else{

        // Shutdown all relays
        relaysShutdown();
        
    }
}
