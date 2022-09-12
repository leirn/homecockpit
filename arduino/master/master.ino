#include <Wire.h> // I2C communications between arduinos
#include <Bounce2.h> // For buttons and switch debouncing
#include <LED.h> // To handle LEDs. Allows led.blink()

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#include "wiring.h" // Pins and wiring definition
#include "protocol.h" // Protocol message codes

U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ SCREEN_CLOCK, /* data=*/ SCREEN_DATA, /* cs=*/ SCREEN_CS, /* dc=*/ SCREEN_DC, /* reset=*/ SCREEN_RESET);

// Lights
// BCN
Bounce2::Button btn_lights_BCN = Bounce2::Button();
LED led_lights_BCN = LED(LED_BCN_PIN);

// LAND
Bounce2::Button btn_lights_LAND = Bounce2::Button();
LED led_lights_LAND = LED(LED_LAND_PIN);

// TAXI
Bounce2::Button btn_lights_TAXI = Bounce2::Button();
LED led_lights_TAXI = LED(LED_TAXI_PIN);

// NAV
Bounce2::Button btn_lights_NAV = Bounce2::Button();
LED led_lights_NAV = LED(LED_NAV_PIN);

// Strobe
Bounce2::Button btn_lights_STRB = Bounce2::Button();
LED led_lights_STRB = LED(LED_STRB_PIN);


// Engine and systems
// Left Pump
Bounce2::Button btn_engine_LPUMP = Bounce2::Button();
LED led_engine_LPUMP = LED(LED_LPUMP_PIN);
// Right Pump
Bounce2::Button btn_engine_RPUMP = Bounce2::Button();
LED led_engine_RPUMP = LED(LED_RPUMP_PIN);
// Carb Head
Bounce2::Button btn_engine_CARB = Bounce2::Button();
LED led_engine_CARB = LED(LED_CARB_PIN);
// Pitot Head
Bounce2::Button btn_engine_PITOT = Bounce2::Button();
LED led_engine_PITOT = LED(LED_PITOT_PIN);
// Anti ice
Bounce2::Button btn_engine_ANTI_ICE = Bounce2::Button();
LED led_engine_ANTI_ICE = LED(LED_ANTI_ICE_PIN);

// Landing gear
Bounce2::Button btn_LDG_GEAR = Bounce2::Button();
LED led_LDG_GEAR_RED = LED(LED_LDG_GEAR_RED_PIN);
LED led_LDG_GEAR_GREEN_LEFT = LED(LED_LDG_GEAR_GREEN_LEFT_PIN);
LED led_LDG_GEAR_GREEN_CENTER = LED(LED_LDG_GEAR_GREEN_CENTER_PIN);
LED led_LDG_GEAR_GREEN_RIGHT = LED(LED_LDG_GEAR_GREEN_RIGHT_PIN);

// Flaps
Bounce2::Button btn_FLAPS_UP = Bounce2::Button();
Bounce2::Button btn_FLAPS_DN = Bounce2::Button();
LED led_FLAPS[4] = {LED(LED_FLAPS_0_PIN), LED(LED_FLAPS_1_PIN), LED(LED_FLAPS_2_PIN), LED(LED_FLAPS_FULL_PIN)};
int current_flaps = 0;

int update_display = 0;
#define LOG_DEPTH 8
String LOG_STACK[LOG_DEPTH];

void logger(String log_string)
{
  update_display = 1;
  for (int i = 0 ; i < LOG_DEPTH - 1 ; i ++)
  {
    LOG_STACK[i] = LOG_STACK[i + 1];
  }
  LOG_STACK[LOG_DEPTH - 1] = log_string;
}

void setup()
{
  for (int i = 0; i < LOG_DEPTH - 1 ; ++i)
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

  logger("Arduino initialized");
}

void loop()
{
  updateButtons();
  readSerialInputFromComputer();
  readSerialInputFromSlave();
  updateDisplay();
}

void updateButtons()
{
  // Lights
  // BCN
  btn_lights_BCN.update();
  if (btn_lights_BCN.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_BCN_OFF);
    logger("BCN light button set to OFF");
  }
  else if (btn_lights_BCN.rose())
  { // Switch moved to ON
    Serial.write(EVENT_BCN_ON);
    logger("BCN light button set to ON");
  }
  // LAND
  btn_lights_LAND.update();
  if (btn_lights_LAND.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_LAND_OFF);
    logger("LAND light button set to OFF");
  }
  else if (btn_lights_LAND.rose())
  { // Switch moved to ON
    Serial.write(EVENT_LAND_ON);
    logger("LAND light button set to ON");
  }
  // TAXI
  btn_lights_TAXI.update();
  if (btn_lights_TAXI.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_TAXI_OFF);
    logger("TAXI light button set to OFF");
  }
  else if (btn_lights_TAXI.rose())
  { // Switch moved to ON
    Serial.write(EVENT_TAXI_ON);
    logger("TAXI light button set to ON");
  }
  // NAV
  btn_lights_NAV.update();
  if (btn_lights_NAV.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_NAV_OFF);
    logger("NAV light button set to OFF");
  }
  else if (btn_lights_NAV.rose())
  { // Switch moved to ON
    Serial.write(EVENT_NAV_ON);
    logger("NAV light button set to ON");
  }
  // Strobe
  btn_lights_STRB.update();
  if (btn_lights_STRB.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_STRB_OFF);
    logger("STRB light button set to OFF");
  }
  else if (btn_lights_STRB.rose())
  { // Switch moved to ON
    Serial.write(EVENT_STRB_ON);
    logger("STRB light button set to ON");
  }

  // Engines
  // Left Pump
  btn_engine_LPUMP.update();
  if (btn_engine_LPUMP.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_LPUMP_OFF);
    logger("Left pump button set to OFF");
  }
  else if (btn_engine_LPUMP.rose())
  { // Switch moved to ON
    Serial.write(EVENT_LPUMP_ON);
    logger("Left pump button set to ON");
  }
  // Right Pump
  btn_engine_RPUMP.update();
  if (btn_engine_RPUMP.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_RPUMP_OFF);
    logger("Right pump button set to OFF");
  }
  else if (btn_engine_RPUMP.rose())
  { // Switch moved to ON
    Serial.write(EVENT_RPUMP_ON);
    logger("Right pump button set to ON");
  }
  // Carb Head
  btn_engine_CARB.update();
  if (btn_engine_CARB.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_CARB_OFF);
    logger("Carb. heat button set to OFF");
  }
  else if (btn_engine_CARB.rose())
  { // Switch moved to ON
    Serial.write(EVENT_CARB_ON);
    logger("Carb. heat button set to ON");
  }
  // Pitot Head
  btn_engine_PITOT.update();
  if (btn_engine_PITOT.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_PITOT_OFF);
    logger("Pitot heat button set to OFF");
  }
  else if (btn_engine_PITOT.rose())
  { // Switch moved to ON
    Serial.write(EVENT_PITOT_ON);
    logger("Pitot heat button set to ON");
  }

  // Anti ice
  btn_engine_ANTI_ICE.update();
  if (btn_engine_ANTI_ICE.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_ANTI_ICE_OFF);
    logger("Anti-ice set button to OFF");
  }
  else if (btn_engine_ANTI_ICE.rose())
  { // Switch moved to ON
    Serial.write(EVENT_ANTI_ICE_ON);
    logger("Anti-ice button set to ON");
  }

  // Landing gear
  btn_LDG_GEAR.update();
  if (btn_LDG_GEAR.fell())
  { // Switch moved to OFF
    Serial.write(EVENT_LDG_GEAR_DN);
    logger("Landing gear button set to DOWN");
  }
  else if (btn_LDG_GEAR.rose())
  { // Switch moved to ON
    Serial.write(EVENT_LDG_GEAR_UP);
    logger("Landing gear button set to UP");
  }

  // Flaps up
  btn_FLAPS_UP.update();
  if (btn_FLAPS_UP.rose() && current_flaps > 0)
  { // Switch moved to ON
    Serial.write(EVENT_FLAPS_DEC);
    logger("FLAPS button pushed to UP");
  }

  // Flaps down
  btn_FLAPS_DN.update();
  if (btn_FLAPS_DN.rose() && current_flaps < 3)
  { // Switch moved to ON
    logger("FLAPS button pushed to DOWN");
  }
}

void readSerialInputFromComputer()
{
  if(Serial.available() > 1)
  {
    int high_byte = Serial.read();
    int low_byte = Serial.read();
    int command = high_byte << 8 + low_byte;
    // TODO : Blink won't work this way
    switch(command) {
      case STATUS_BCN_OFF:
        led_lights_BCN.off();
        logger("MSG RCV: BCN to OFF");
        break;
      case STATUS_BCN_ON:
        led_lights_BCN.on();
        logger("MSG RCV: BCN to ON");
        break;
      case STATUS_BCN_ERROR:
        led_lights_BCN.blink(0, 1000);
        logger("MSG RCV: BCN to ERROR");
        break;
      case STATUS_TAXI_OFF:
        led_lights_TAXI.off();
        logger("MSG RCV: TAXI to OFF");
        break;
      case STATUS_TAXI_ON:
        led_lights_TAXI.on();
        logger("MSG RCV: TAXI to ON");
        break;
      case STATUS_TAXI_ERROR:
        led_lights_TAXI.blink(0, 1000);
        logger("MSG RCV: TAXI to ERROR");
        break;
      case STATUS_LAND_OFF:
        led_lights_LAND.off();
        logger("MSG RCV: LAND to OFF");
        break;
      case STATUS_LAND_ON:
        led_lights_LAND.on();
        logger("MSG RCV: LAND to ON");
        break;
      case STATUS_LAND_ERROR:
        led_lights_LAND.blink(0, 1000);
        logger("MSG RCV: LAND to ERROR");
        break;
      case STATUS_NAV_OFF:
        led_lights_NAV.off();
        logger("MSG RCV: NAV to OFF");
        break;
      case STATUS_NAV_ON:
        led_lights_NAV.on();
        logger("MSG RCV: NAV to ON");
        break;
      case STATUS_NAV_ERROR:
        led_lights_NAV.blink(0, 1000);
        logger("MSG RCV: NAV to ERROR");
        break;
      case STATUS_STRB_OFF:
        led_lights_STRB.off();
        logger("MSG RCV: STRB to OFF");
        break;
      case STATUS_STRB_ON:
        led_lights_STRB.on();
        logger("MSG RCV: STRB to ON");
        break;
      case STATUS_STRB_ERROR:
        led_lights_STRB.blink(0, 1000);
        logger("MSG RCV: STRB to ERROR");
        break;
      case STATUS_LPUMP_OFF:
        led_engine_LPUMP.off();
        logger("MSG RCV: LPUMP to OFF");
        break;
      case STATUS_LPUMP_ON:
        led_engine_LPUMP.on();
        logger("MSG RCV: LPUMP to ON");
        break;
      case STATUS_LPUMP_ERROR:
        led_engine_LPUMP.blink(0, 1000);
        logger("MSG RCV: LPUMP to ERROR");
        break;
      case STATUS_RPUMP_OFF:
        led_engine_RPUMP.off();
        logger("MSG RCV: RPUMP to OFF");
        break;
      case STATUS_RPUMP_ON:
        led_engine_RPUMP.on();
        logger("MSG RCV: RPUMP to ON");
        break;
      case STATUS_RPUMP_ERROR:
        led_engine_RPUMP.blink(0, 1000);
        logger("MSG RCV: RPUMP to ERROR");
        break;
      case STATUS_CARB_OFF:
        led_engine_CARB.off();
        logger("MSG RCV: CARB HEAT to OFF");
        break;
      case STATUS_CARB_ON:
        led_engine_CARB.on();
        logger("MSG RCV: CARB HEAT to ON");
        break;
      case STATUS_CARB_ERROR:
        led_engine_ANTI_ICE.blink(0, 1000);
        logger("MSG RCV: CARB HEAT to ERROR");
        break;
      case STATUS_ANTI_ICE_OFF:
        led_engine_ANTI_ICE.off();
        logger("MSG RCV: ANTI ICE to OFF");
        break;
      case STATUS_ANTI_ICE_ON:
        led_engine_ANTI_ICE.on();
        logger("MSG RCV: ANTI ICE to ON");
        break;
      case STATUS_ANTI_ICE_ERROR:
        led_engine_ANTI_ICE.blink(0, 1000);
        logger("MSG RCV: ANTI ICE to ERROR");
        break;
      case STATUS_PITOT_OFF:
        led_engine_PITOT.off();
        logger("MSG RCV: PITOT HEAT to OFF");
        break;
      case STATUS_PITOT_ON:
        led_engine_PITOT.on();
        logger("MSG RCV: PITOT HEAT to ON");
        break;
      case STATUS_PITOT_ERROR:
        led_engine_PITOT.blink(0, 1000);
        logger("MSG RCV: PITOT HEAT to ERROR");
        break;
      // TODO : define right behaviour for red. Will require internal states. Red when moving ?
      case STATUS_LDG_GEAR_CENTER_UP:
        led_LDG_GEAR_GREEN_CENTER.off();
        logger("MSG RCV: CENTER LDG GEAR to UP");
        break;
      case STATUS_LDG_GEAR_CENTER_DOWN:
        led_LDG_GEAR_GREEN_CENTER.on();
        logger("MSG RCV: CENTER LDG GEAR to DOWN");
        break;
      case STATUS_LDG_GEAR_CENTER_UNKNOWN:
        led_LDG_GEAR_GREEN_CENTER.off();
        logger("MSG RCV: TCENTER LDG GEAR to UNKNOWN");
        break;
      case STATUS_LDG_GEAR_LEFT_UP:
        led_LDG_GEAR_GREEN_LEFT.off();
        logger("MSG RCV: LEFT LDG GEAR to UP");
        break;
      case STATUS_LDG_GEAR_LEFT_DOWN:
        led_LDG_GEAR_GREEN_LEFT.on();
        logger("MSG RCV: LEFT LDG GEAR to DOWN");
        break;
      case STATUS_LDG_GEAR_LEFT_UNKNOWN:
        led_LDG_GEAR_GREEN_LEFT.off();
        logger("MSG RCV: LEFT LDG GEAR to UNKNOWN");
        break;
      case STATUS_LDG_GEAR_RIGHT_UP:
        led_LDG_GEAR_GREEN_RIGHT.off();
        logger("MSG RCV: RIGHT LDG GEAR to UP");
        break;
      case STATUS_LDG_GEAR_RIGHT_DOWN:
        led_LDG_GEAR_GREEN_RIGHT.on();
        logger("MSG RCV: RIGHT LDG GEAR to DOWN");
        break;
      case STATUS_LDG_GEAR_RIGHT_UNKNOWN:
        led_LDG_GEAR_GREEN_RIGHT.off();
        logger("MSG RCV: RIGHT LDG GEAR to UNKNOWN");
        break;
      default:
        char buffer[26];
        sprintf_P(buffer,PSTR("Unknow command : 0x%02x"), command);
        logger(buffer);
        break;
    }
  }
}

void readSerialInputFromSlave()
{
}

void updateDisplay()
{
  if (update_display)
  {
    u8g2.clearBuffer();
    for (int i = 0 ; i < LOG_DEPTH ; ++i)
    {
      u8g2.drawStr(1 + 16 * i, 1, LOG_STACK[i].c_str());
    }
    u8g2.sendBuffer();
    update_display = 0;
  }
}
