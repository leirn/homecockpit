#include <Wire.h> // I2C communications between arduinos
#include <Bounce2.h> // For buttons and switch debouncing
#include <LED.h> // To handle LEDs. Allows led.blink()

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 6, /* data=*/ 5, /* cs=*/ 2, /* dc=*/ 3, /* reset=*/ 4);

// Lights
// BCN
Bounce2::Button btn_lights_BCN = Bounce2::Button();
#define BTN_BCN_PIN 33
#define LED_BCN_PIN 32
LED led_lights_BCN = LED(LED_BCN_PIN);
#define EVENT_BCN_ON 0x1011
#define EVENT_BCN_OFF 0x1010

// LAND
Bounce2::Button btn_lights_LAND = Bounce2::Button();
#define BTN_LAND_PIN 35
#define LED_LAND_PIN 34
LED led_lights_LAND = LED(LED_LAND_PIN);
#define EVENT_LAND_ON 0x1021
#define EVENT_LAND_OFF 0x1020

// TAXI
Bounce2::Button btn_lights_TAXI = Bounce2::Button();
#define BTN_TAXI_PIN 37
#define LED_TAXI_PIN 36
LED led_lights_TAXI = LED(LED_TAXI_PIN);
#define EVENT_TAXI_ON 0x1031
#define EVENT_TAXI_OFF 0x1030

// NAV
Bounce2::Button btn_lights_NAV = Bounce2::Button();
#define BTN_NAV_PIN 39
#define LED_NAV_PIN 38
LED led_lights_NAV = LED(LED_NAV_PIN);
#define EVENT_NAV_ON 0x1041
#define EVENT_NAV_OFF 0x1040

// Strobe
Bounce2::Button btn_lights_STRB = Bounce2::Button();
#define BTN_STRB_PIN 41
#define LED_STRB_PIN 40
LED led_lights_STRB = LED(LED_STRB_PIN);
#define EVENT_STRB_ON 0x1051
#define EVENT_STRB_OFF 0x1050


// Engine and systems
// Left Pump
Bounce2::Button btn_engine_LPUMP = Bounce2::Button();
#define BTN_LPUMP_PIN 23
#define LED_LPUMP_PIN 22
LED led_engine_LPUMP = LED(LED_LPUMP_PIN);
#define EVENT_LPUMP_ON 0x2011
#define EVENT_LPUMP_OFF 0x2010
// Right Pump
Bounce2::Button btn_engine_RPUMP = Bounce2::Button();
#define BTN_RPUMP_PIN 25
#define LED_RPUMP_PIN 24
LED led_engine_RPUMP = LED(LED_RPUMP_PIN);
#define EVENT_RPUMP_ON 0x2021
#define EVENT_RPUMP_OFF 0x2020
// Carb Head
Bounce2::Button btn_engine_CARB = Bounce2::Button();
#define BTN_CARB_PIN 27
#define LED_CARB_PIN 26
LED led_engine_CARB = LED(LED_CARB_PIN);
#define EVENT_CARB_ON 0x2031
#define EVENT_CARB_OFF 0x2030
// Pitot Head
Bounce2::Button btn_engine_PITOT = Bounce2::Button();
#define BTN_PITOT_PIN 29
#define LED_PITOT_PIN 28
LED led_engine_PITOT = LED(LED_PITOT_PIN);
#define EVENT_PITOT_ON 0x6011
#define EVENT_PITOT_OFF 0x6010
// Anti ice
Bounce2::Button btn_engine_ANTI_ICE = Bounce2::Button();
#define BTN_ANTI_ICE_PIN 31
#define LED_ANTI_ICE_PIN 30
LED led_engine_ANTI_ICE = LED(LED_ANTI_ICE_PIN);
#define EVENT_ANTI_ICE_ON 0xffff
#define EVENT_ANTI_ICE_OFF 0xffff

// Landing gear
Bounce2::Button btn_LDG_GEAR = Bounce2::Button();
#define BTN_LDG_GEAR_PIN 46
#define LED_LDG_GEAR_RED_PIN 42
LED led_LDG_GEAR_RED = LED(LED_LDG_GEAR_RED_PIN);
#define LED_LDG_GEAR_GREEN_LEFT_PIN 43
LED led_LDG_GEAR_GREEN_LEFT = LED(LED_LDG_GEAR_GREEN_LEFT_PIN);
#define LED_LDG_GEAR_GREEN_CENTER_PIN 44
LED led_LDG_GEAR__GREEN_CENTER = LED(LED_LDG_GEAR_GREEN_CENTER_PIN);
#define LED_LDG_GEAR_GREEN_RIGHT_PIN 45
LED led_LDG_GEAR_GREEN_RIGHT = LED(LED_LDG_GEAR_GREEN_RIGHT_PIN);
#define EVENT_LDG_GEAR_UP 0x6020
#define EVENT_LDG_GEAR_DN 0x6021

// Flaps
Bounce2::Button btn_FLAPS_UP = Bounce2::Button();
#define BTN_FLAPS_UP_PIN 51
Bounce2::Button btn_FLAPS_DN = Bounce2::Button();
#define BTN_FLAPS_DN_PIN 52
#define LED_FLAPS_0_PIN 47
#define LED_FLAPS_1_PIN 48
#define LED_FLAPS_2_PIN 49
#define LED_FLAPS_FULL_PIN 50
LED led_FLAPS[4];
led_FLAPS[0] = LED(LED_FLAPS_0_PIN);
led_FLAPS[1] = LED(LED_FLAPS_1_PIN);
led_FLAPS[2] = LED(LED_FLAPS_2_PIN);
led_FLAPS[3] = LED(LED_FLAPS_FULL_PIN);
int current_flaps = 0;
#define EVENT_FLAPS_INC 0x6061
#define EVENT_FLAPS_DEC 0x6060

int update_display = 0;
LOG_DEPTH = 8;
String LOG_STACK[LOG_DEPTH];

void setup()
{
    for(i = 0; i < LOG_DEPTH - 1 ; i++)
    {
        LOG_STACK[0] = " ";
    }
    LOG_STACK[LOG_DEPTH - 1] = "Initialization started...";
    
    // Initializing screen
    u8g2.begin();   
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    update_display = 1;
    
    Serial.begin(9600); // Init Serial interface

    // Initiate lights
    // BCN
    btn_lights_BCN.attach(BTN_BCN_PIN, INPUT_PULLUP);
    btn_lights_BCN.interval(25);
    // LAND
    btn_lights_LAND.attach(BTN_LAND_PIN, INPUT_PULLUP);
    btn_lights_LAND.interval(25);
    // TAXI
    btn_lights_TAXI.attach(BTN_TAXI_PIN, INPUT_PULLUP);
    btn_lights_TAXI.interval(25);
    // NAV
    btn_lights_NAV.attach(BTN_NAV_PIN, INPUT_PULLUP);
    btn_lights_NAV.interval(25);
    // Strobe
    btn_lights_STRB.attach(BTN_STRB_PIN, INPUT_PULLUP);
    btn_lights_STRB.interval(25);

    // Engine and systems
    // Left Pump
    btn_engine_LPUMP.attach(BTN_LPUMP_PIN, INPUT_PULLUP);
    btn_engine_LPUMP.interval(25);
    // Right Pump
    btn_engine_RPUMP.attach(BTN_RPUMP_PIN, INPUT_PULLUP);
    btn_engine_RPUMP.interval(25);
    // Carb Heat
    btn_engine_CARB.attach(BTN_CARB_PIN, INPUT_PULLUP);
    btn_engine_CARB.interval(25);
    // Pitot Heat
    btn_engine_PITOT.attach(BTN_PITOT_PIN, INPUT_PULLUP);
    btn_engine_PITOT.interval(25);
    // Anti-ice
    btn_engine_ANTI_ICE.attach(BTN_ANTI_ICE_PIN, INPUT_PULLUP);
    btn_engine_ANTI_ICE.interval(25);
    
    // Landing Gear
    btn_LDG_GEAR.attach(BTN_LDG_GEAR_PIN, INPUT_PULLUP);
    btn_LDG_GEAR.interval(25);
    
    // Flaps
    btn_FLAPS_UP.attach(BTN_FLAPS_UP_PIN, INPUT_PULLUP);
    btn_FLAPS_UP.interval(25);
    btn_FLAPS_DN.attach(BTN_FLAPS_DN_PIN, INPUT_PULLUP);
    btn_FLAPS_DN.interval(25);
}

void loop()
{
    updateButtons();
    readSerialInputFromComputer();
    readSerialInputFromSlave();
    updateDisplay();
}

void updateButtons() {
    // Lights
    // BCN
    btn_lights_BCN.update();
    if (btn_lights_BCN.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_BCN_OFF);
        led_lights_BCN.off();
        log("BCN light set to OFF");
    }
    else if (btn_lights_BCN.rose())
    { // Switch moved to ON
        Serial.write(EVENT_BCN_ON);
        led_lights_BCN.on();
        log("BCN light set to ON");
    }
    // LAND
    btn_lights_LAND.update();
    if (btn_lights_LAND.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LAND_OFF);
        led_lights_LAND.off();
        log("LAND light set to OFF");
    }
    else if (btn_lights_LAND.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LAND_ON);
        led_lights_LAND.on();
        log("LAND light set to ON");
    }
    // TAXI
    btn_lights_TAXI.update();
    if (btn_lights_TAXI.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_TAXI_OFF);
        led_lights_TAXI.off();
        log("TAXI light set to OFF");
    }
    else if (btn_lights_TAXI.rose())
    { // Switch moved to ON
        Serial.write(EVENT_TAXI_ON);
        led_lights_TAXI.on();
        log("TAXI light set to ON");
    }
    // NAV
    btn_lights_NAV.update();
    if (btn_lights_NAV.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_NAV_OFF);
        led_lights_NAV.off();
        log("NAV light set to OFF");
    }
    else if (btn_lights_NAV.rose())
    { // Switch moved to ON
        Serial.write(EVENT_NAV_ON);
        led_lights_NAV.on();
        log("NAV light set to ON");
    }
    // Strobe
    btn_lights_STRB.update();
    if (btn_lights_STRB.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_STRB_OFF);
        led_lights_STRB.off();
        log("STRB light set to OFF");
    }
    else if (btn_lights_STRB.rose())
    { // Switch moved to ON
        Serial.write(EVENT_STRB_ON);
        led_lights_STRB.on();
        log("STRB light set to ON");
    }

    // Engines
    // Left Pump
    btn_engine_LPUMP.update();
    if (btn_engine_LPUMP.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LPUMP_OFF);
        led_engine_LPUMP.off();
        log("Left pump set to OFF");
    }
    else if (btn_engine_LPUMP.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LPUMP_ON);
        led_engine_LPUMP.on();
        log("Left pump set to ON");
    }
    // Right Pump
    btn_engine_RPUMP.update();
    if (btn_engine_RPUMP.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_RPUMP_OFF);
        led_engine_LPUMP.off();
        log("Right pump set to OFF");
    }
    else if (btn_engine_RPUMP.rose())
    { // Switch moved to ON
        Serial.write(EVENT_RPUMP_ON);
        led_engine_RPUMP.on();
        log("Right pump set to ON");
    }
    // Carb Head
    btn_engine_CARB.update();
    if (btn_engine_CARB.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_CARB_OFF);
        led_engine_CARB.off();
        log("Carb. heat set to OFF");
    }
    else if (btn_engine_CARB.rose())
    { // Switch moved to ON
        Serial.write(EVENT_CARB_ON);
        led_engine_CARB.on();
        log("Carb. heat set to ON");
    }
    // Pitot Head
    btn_engine_PITOT.update();
    if (btn_engine_PITOT.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_PITOT_OFF);
        led_engine_PITOT.off();
        log("Pitot heat set to OFF");
    }
    else if (btn_engine_PITOT.rose())
    { // Switch moved to ON
        Serial.write(EVENT_PITOT_ON);
        led_engine_PITOT.on();
        log("Pitot heat set to ON");
    }}
    // Anti ice
    btn_engine_ANTI_ICE.update();
    if (btn_engine_ANTI_ICE.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_ANTI_ICE_OFF);
        led_engine_ANTI_ICE.off();
        log("Anti-ice set to OFF");
    }
    else if (btn_engine_ANTI_ICE.rose())
    { // Switch moved to ON
        Serial.write(EVENT_ANTI_ICE_ON);
        led_engine_ANTI_ICE.on();
        log("Anti-ice set to ON");
    }

    // Landing gear
    btn_LDG_GEAR.update();
    if (btn_LDG_GEAR.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LDG_GEAR_DN);
        led_engine_ANTI_ICE.off(); 
        led_LDG_GEAR_GREEN_LEFT.on();
        led_LDG_GEAR_GREEN_CENTER.on();
        led_LDG_GEAR_GREEN_RIGHT.on();
        log("Landing gear set to DOWN");
    }
    else if (btn_LDG_GEAR.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LDG_GEAR_UP);
        led_LDG_GEAR_RED.off();
        led_LDG_GEAR_GREEN_LEFT.off();
        led_LDG_GEAR_GREEN_CENTER.off();
        led_LDG_GEAR_GREEN_RIGHT.off();
        log("Landing gear set to UP");
    }

    // Flaps up
    btn_FLAPS_UP.update();
    if (btn_FLAPS_UP.rose() && current_flaps > 0)
    { // Switch moved to ON
        led_FLAPS[current_flaps].off();
        ccurrent_flaps--;
        led_FLAPS[current_flaps].on();
        Serial.write(EVENT_FLAPS_DEC);
        log("FLAPS DECREMENTED");
    }

    // Flaps down
    btn_FLAPS_Dn.update();
    if (btn_FLAPS_DN.rose() && current_flaps < 3)
    { // Switch moved to ON
        led_FLAPS[current_flaps].off();
        ccurrent_flaps++;
        led_FLAPS[current_flaps].on();
        Serial.write(EVENT_FLAPS_INC);
        log("FLAPS INCREMENTED");
    }
}

void readSerialInputFromComputer()
{
}

void readSerialInputFromSlave()
{
}

void updateDisplay()
{
    if(update_display)
    {
        u8g2.clearBuffer();
        for(i = 0 ; i < LOG_DEPTH ; i++)
        {
            u8g2.drawStr(1 + 16 * i, 1, LOG_STACK[i].c_str());
        }
        u8g2.sendBuffer();
        update_display = 0;
    }
}

void log(String log)
{
    update_display = 1;
    delete LOG_STACK[0]
    for(i=0 ; i < LOG_DEPTH - 1 ; i ++)
    {
        LOG_STACK[i] = LOG_STACK[i + 1];
    }
    LOG_STACK[LOG_DEPTH - 1] = log;
}
