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
 *  [ System menu file ]
 */

// Menu variables

MenuSystem ms;
Menu mm(STR_MENU_NAME);
MenuItem set_on_off(STR_MENU_SYSTEM_STATE);
MenuItem set_sound(STR_MENU_SOUND);
MenuItem set_temperature(STR_MENU_SET_TEMP);
MenuItem set_humidity(STR_MENU_SET_HUMIDITY);
MenuItem set_temp_margin(STR_MENU_TEMP_MARGIN);
MenuItem set_humi_margin(STR_MENU_HUMI_MARGIN);
MenuItem save_config(STR_MENU_SAVE_EXIT);
MenuItem exit_menu(STR_MENU_EXIT);

unsigned int manualTimeout = 0;
unsigned int MAX_TEMP = (DHT_FAHRENHEIT)? dht.convertCtoF(50):50;

// Menu helpers

void displayMenu() {
    menuActive = true;
    
    lcd.clear();
    lcd.setCursor(0,0);
    
    // Display the menu
    Menu const* cp_menu = ms.get_current_menu();
    lcd.print(cp_menu->get_name());
    lcd.setCursor(0,1);
    lcd.print(cp_menu->get_selected()->get_name());

    backlightOn();
}

// Menu callback function

void on_set_on_off(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_SYSTEM_STATE);
    delay(500); // simulate transition

    int cursorPosition = 14;
    uint8_t pressedBtn;
    defaultTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        char* activ = (arduClimaSettings.systemOn)? STR_ON:STR_OFF;
        sprintf(buffer, "%-12s %3s", STR_SYSTEM_STATE, activ);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_inputs();
      
        switch (pressedBtn){
            case BTN_UP: // Active
            case 1: // Active

                arduClimaSettings.systemOn = true;
                break;
                
            case BTN_DOWN: // Inactive
            case 0: // Inactive
            
                arduClimaSettings.systemOn = false;
        }

    }while(pressedBtn != BTN_SELECT);

    if (arduClimaSettings.systemOn) buzzer(2, 10);
    else buzzer(3, 10);

    delay(DELAY_ON_BTN_PRESS);
    
    defaultTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_set_temperature(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_TEMP_AVG);
    delay(500); // simulate transition

    int cursorPosition = 13;
    uint8_t pressedBtn;
    defaultTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        char* temp_unit = (DHT_FAHRENHEIT)? STR_TEMP_SET_F:STR_TEMP_SET_C;
        sprintf(buffer, "%-11s %3d", temp_unit, arduClimaSettings.temperature);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(15,1);
        lcd.write(byte(1));
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_inputs();

        if (pressedBtn < 10){
            arduClimaSettings.temperature = pressedBtn;
        }else{
            switch (pressedBtn){
                case BTN_UP: // Add
    
                    arduClimaSettings.temperature += TEMPERATURE_STEP;
                    break;
                    
                case BTN_DOWN: // Substract
    
                    arduClimaSettings.temperature -= TEMPERATURE_STEP;
            }
        }

        if (arduClimaSettings.temperature < 0) arduClimaSettings.temperature = MAX_TEMP;
        else if (arduClimaSettings.temperature > MAX_TEMP) arduClimaSettings.temperature = 0;

    }while(pressedBtn != BTN_SELECT);

    defaultTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_set_humidity(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_HUMI_AVG);
    delay(500); // simulate transition

    int cursorPosition = 13;
    uint8_t pressedBtn;
    defaultTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "%-11s %3d", STR_HUMI_SET, arduClimaSettings.humidity);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(15,1);
        lcd.write(byte(2));
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_inputs();

        if (pressedBtn == 0){
            arduClimaSettings.humidity = 0;
        }else{
            switch (pressedBtn){
                case BTN_UP: // Add
    
                    arduClimaSettings.humidity += HUMIDITY_STEP;
                    break;
                    
                case BTN_DOWN: // Substract
    
                    arduClimaSettings.humidity -= HUMIDITY_STEP;
            }
        }

        if (arduClimaSettings.humidity < 0) arduClimaSettings.humidity = 100;
        else if (arduClimaSettings.humidity > 100) arduClimaSettings.humidity = 0;

    }while(pressedBtn != BTN_SELECT);

    defaultTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_set_temp_margin(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_TEMP_MARGIN);
    delay(500); // simulate transition

    int cursorPosition = 13;
    uint8_t pressedBtn;
    defaultTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        char* temp_unit = (DHT_FAHRENHEIT)? STR_TEMP_SET_F:STR_TEMP_SET_C;
        sprintf(buffer, "%-12s %2d", temp_unit, arduClimaSettings.tempMargin);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(15,1);
        lcd.write(byte(1));
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_inputs();

        if (pressedBtn < 10){
            arduClimaSettings.tempMargin = pressedBtn;
        }else{
            switch (pressedBtn){
                case BTN_UP: // Add
    
                    arduClimaSettings.tempMargin ++;
                    break;
                    
                case BTN_DOWN: // Substract
    
                    arduClimaSettings.tempMargin --;
            }
        }

        if (arduClimaSettings.tempMargin < 0) arduClimaSettings.tempMargin = 20;
        else if (arduClimaSettings.tempMargin > 20) arduClimaSettings.tempMargin = 0;

    }while(pressedBtn != BTN_SELECT);

    defaultTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_set_humi_margin(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_HUMI_MARGIN);
    delay(500); // simulate transition

    int cursorPosition = 13;
    uint8_t pressedBtn;
    defaultTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "%-12s %2d", STR_HUMI_SET, arduClimaSettings.humiMargin);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(15,1);
        lcd.write(byte(2));
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_inputs();

        if (pressedBtn < 10){
            arduClimaSettings.humiMargin = pressedBtn;
        }else{
            switch (pressedBtn){
                case BTN_UP: // Add
    
                    arduClimaSettings.humiMargin ++;
                    break;
                    
                case BTN_DOWN: // Substract
    
                    arduClimaSettings.humiMargin --;
            }
        }

        if (arduClimaSettings.humiMargin < 0) arduClimaSettings.humiMargin = 20;
        else if (arduClimaSettings.humiMargin > 20) arduClimaSettings.humiMargin = 0;

    }while(pressedBtn != BTN_SELECT);

    defaultTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_set_sound(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_SOUND);
    delay(500); // simulate transition

    int cursorPosition = 14;
    uint8_t pressedBtn;
    defaultTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        char* activ = (arduClimaSettings.soundOn)? STR_ON:STR_OFF;
        sprintf(buffer, "%-12s %3s", STR_SOUND, activ);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_inputs();
      
        switch (pressedBtn){
            case BTN_UP: // Active
            case 1: // Active

                arduClimaSettings.soundOn = true;
                break;
                
            case BTN_DOWN: // Inactive
            case 0: // Inactive
            
                arduClimaSettings.soundOn = false;
        }

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);
    
    defaultTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_save_config(MenuItem* p_menu_item){
    buzzer(2, 20);
    writeParams(0);
    ms.reset();
    menuActive = false;
}

void on_exit_menu(MenuItem* p_menu_item){
    buzzer(1, 100);
    ms.reset();
    menuActive = false;
}

// Create menu in memory

void createMenu(){
    mm.add_item(&set_on_off, &on_set_on_off);
    mm.add_item(&set_temperature, &on_set_temperature);
    mm.add_item(&set_humidity, &on_set_humidity);
    mm.add_item(&set_temp_margin, &on_set_temp_margin);
    mm.add_item(&set_humi_margin, &on_set_humi_margin);
    mm.add_item(&set_sound, &on_set_sound);
    mm.add_item(&save_config, &on_save_config);
    mm.add_item(&exit_menu, &on_exit_menu);
    ms.set_root_menu(&mm);
}

