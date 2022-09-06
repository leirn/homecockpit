#include <Wire.h> // I2C communications between arduinos
#include <Bounce2.h> // For buttons and switch debouncing
#include <LED.h> // To handle LEDs. Allows led.blink()

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

void setup()
{
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
    // Righut Pump
    btn_engine_RPUMP.attach(BTN_RPUMP_PIN, INPUT_PULLUP);
    btn_engine_RPUMP.interval(25);
}

void loop()
{
    // Lights
    // BCN
    btn_lights_BCN.update();
    if (btn_lights_BCN.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_BCN_OFF);
        led_lights_BCN.off();
    }
    else if (btn_lights_BCN.rose())
    { // Switch moved to ON
        Serial.write(EVENT_BCN_ON);
        led_lights_BCN.on();
    }
    // LAND
    btn_lights_LAND.update();
    if (btn_lights_LAND.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LAND_OFF);
        led_lights_LAND.off();
    }
    else if (btn_lights_LAND.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LAND_ON);
        led_lights_LAND.on();
    }
    // TAXI
    btn_lights_TAXI.update();
    if (btn_lights_TAXI.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_TAXI_OFF);
        led_lights_TAXI.off();
    }
    else if (btn_lights_TAXI.rose())
    { // Switch moved to ON
        Serial.write(EVENT_TAXI_ON);
        led_lights_TAXI.on();
    }
    // NAV
    btn_lights_NAV.update();
    if (btn_lights_NAV.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_NAV_OFF);
        led_lights_NAV.off();
    }
    else if (btn_lights_NAV.rose())
    { // Switch moved to ON
        Serial.write(EVENT_NAV_ON);
        led_lights_NAV.on();
    }
    // Strobe
    btn_lights_STRB.update();
    if (btn_lights_STRB.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_STRB_OFF);
        led_lights_STRB.off();
    }
    else if (btn_lights_STRB.rose())
    { // Switch moved to ON
        Serial.write(EVENT_STRB_ON);
        led_lights_STRB.on();
    }

    // Engines
    // Left Pump
    btn_engine_LPUMP.update();
    if (btn_engine_LPUMP.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LPUMP_OFF);
        led_engine_LPUMP.off();
    }
    else if (btn_engine_LPUMP.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LPUMP_ON);
        led_engine_LPUMP.on();
    }
    // Right Pump
    btn_engine_RPUMP.update();
    if (btn_engine_RPUMP.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_RPUMP_OFF);
        led_engine_LPUMP.off();
    }
    else if (btn_engine_RPUMP.rose())
    { // Switch moved to ON
        Serial.write(EVENT_RPUMP_ON);
        led_engine_RPUMP.on();
    }
}
