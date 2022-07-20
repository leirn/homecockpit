#include <Wire.h> // I2C communications between arduinos
#include <Bounce2.h> // For buttons and switch debouncing

// Lights
// BCN
Bounce2::Button btn_lights_BCN = Bounce2::Button();
#define BTN_BCN_PIN 4 // TO BE CHANGED
#define LED_BCN_PIN 5 // TO BE CHANGED
#define EVENT_BCN_ON 0x1011
#define EVENT_BCN_OFF 0x1010

// LAND
Bounce2::Button btn_lights_LAND = Bounce2::Button();
#define BTN_LAND_PIN 6 // TO BE CHANGED
#define LED_LAND_PIN 7 // TO BE CHANGED
#define EVENT_LAND_ON 0x1021
#define EVENT_LAND_OFF 0x1020

// TAXI
Bounce2::Button btn_lights_TAXI = Bounce2::Button();
#define BTN_TAXI_PIN 8 // TO BE CHANGED
#define LED_TAXI_PIN 9 // TO BE CHANGED
#define EVENT_TAXI_ON 0x1031
#define EVENT_TAXI_OFF 0x1030

// NAV
Bounce2::Button btn_lights_NAV = Bounce2::Button();
#define BTN_NAV_PIN 10 // TO BE CHANGED
#define LED_NAV_PIN 11 // TO BE CHANGED
#define EVENT_NAV_ON 0x1041
#define EVENT_NAV_OFF 0x1040

// Strobe
Bounce2::Button btn_lights_STRB = Bounce2::Button();
#define BTN_STRB_PIN 12 // TO BE CHANGED
#define LED_STRB_PIN 13 // TO BE CHANGED
#define EVENT_STRB_ON 0x1051
#define EVENT_STRB_OFF 0x1050


// Engine and systems
// Left Pump
Bounce2::Button btn_engine_LPUMP = Bounce2::Button();
#define BTN_LPUMP_PIN 14 // TO BE CHANGED
#define LED_LPUMP_PIN 15 // TO BE CHANGED
#define EVENT_LPUMP_ON 0x2011
#define EVENT_LPUMP_OFF 0x2010
// Right Pump
Bounce2::Button btn_engine_RPUMP = Bounce2::Button();
#define BTN_RPUMP_PIN 16 // TO BE CHANGED
#define LED_RPUMP_PIN 17 // TO BE CHANGED
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
        Serial.write(EVENT_BCN_ON);
        digitalWrite(LED_BCN_PIN, HIGH);
    }
    else if (btn_lights_BCN.rose())
    { // Switch moved to ON
        Serial.write(EVENT_BCN_OFF);
        digitalWrite(LED_BCN_PIN, LOW);
    }
    // LAND
    btn_lights_LAND.update();
    if (btn_lights_LAND.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LAND_ON);
        digitalWrite(LED_LAND_PIN, HIGH);
    }
    else if (btn_lights_LAND.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LAND_OFF);
        digitalWrite(LED_LAND_PIN, LOW);
    }
    // TAXI
    btn_lights_TAXI.update();
    if (btn_lights_TAXI.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_TAXI_ON);
        digitalWrite(LED_TAXI_PIN, HIGH);
    }
    else if (btn_lights_TAXI.rose())
    { // Switch moved to ON
        Serial.write(EVENT_TAXI_OFF);
        digitalWrite(LED_TAXI_PIN, LOW);
    }
    // NAV
    btn_lights_NAV.update();
    if (btn_lights_NAV.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_NAV_ON);
        digitalWrite(LED_NAV_PIN, HIGH);
    }
    else if (btn_lights_NAV.rose())
    { // Switch moved to ON
        Serial.write(EVENT_NAV_OFF);
        digitalWrite(LED_NAV_PIN, LOW);
    }
    // Strobe
    btn_lights_STRB.update();
    if (btn_lights_STRB.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_STRB_ON);
        digitalWrite(LED_STRB_PIN, HIGH);
    }
    else if (btn_lights_STRB.rose())
    { // Switch moved to ON
        Serial.write(EVENT_STRB_OFF);
        digitalWrite(LED_STRB_PIN, LOW);
    }

    // Engines
    // Left Pump
    btn_engine_LPUMP.update();
    if (btn_engine_LPUMP.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_LPUMP_ON);
        digitalWrite(LED_LPUMP_PIN, HIGH);
    }
    else if (btn_engine_LPUMP.rose())
    { // Switch moved to ON
        Serial.write(EVENT_LPUMP_OFF);
        digitalWrite(LED_LPUMP_PIN, LOW);
    }
    // Right Pump
    btn_engine_RPUMP.update();
    if (btn_engine_RPUMP.fell())
    { // Switch moved to OFF
        Serial.write(EVENT_RPUMP_ON);
        digitalWrite(LED_RPUMP_PIN, HIGH);
    }
    else if (btn_engine_RPUMP.rose())
    { // Switch moved to ON
        Serial.write(EVENT_RPUMP_OFF);
        digitalWrite(LED_RPUMP_PIN, LOW);
    }
}