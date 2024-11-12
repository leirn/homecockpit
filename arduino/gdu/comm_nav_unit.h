/**
 * This class allows to interact with a COMM NAV module
 */

#ifndef comm_nav_unit_h
#define comm_nav_unit_h

// #define DEBUG 1

#include <Arduino.h>

#include <Adafruit_MCP23X17.h>

#define COUNT_FALLING 0
#define COUNT_RISING 1
#define COUNT_BOTH 2

#define COMM_NAV_BUTTON_COUNT 14

const int BUTTON_PINS[COMM_NAV_BUTTON_COUNT] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
};

const String SIMCONNECT_COMM_NAV[12]{
    "NAV_SWAP_ACTIVE",
    "NAV_MENU",
    "NAV_KNOB_INC_1MHZ",
    "NAV_KNOB_DEC_1MHZ",
    "NAV_KNOB_INC_FRAC",
    "NAV_KNOB_DEC_FRAC",
    "NAV_KNOB_DEC_PUSH",
    "COMM_SWAP_ACTIVE",
    "COMM_MENU",
    "COMM_KNOB_INC_1MHZ",
    "COMM_KNOB_DEC_1MHZ",
    "COMM_KNOB_INC_FRAC",
    "COMM_KNOB_DEC_FRAC",
    "COMM_KNOB_DEC_PUSH",
};

class gdu_unit
{
private:
  // Connection to MCP23S17
  Adafruit_MCP23X17 mcp;

  unsigned long debounceTime;
  unsigned long count[12];
  int countMode[12];
  int pressedState[12];   // the state when the button is considered pressed
  int unpressedState[12]; // the state when the button is considered unpressed

  int previousSteadyState[12];  // the previous steady state from the input pin, used to detect pressed and released event
  int lastSteadyState[12];      // the last steady state from the input pin
  int lastFlickerableState[12]; // the last flickerable state from the input pin

  unsigned long lastDebounceTime[12]; // the last time the output pin was toggled

public:
  gdu_unit();
  void begin(int cs_pin, int a_code);
  void setDebounceTime(unsigned long time);
  int getState(int button_id);
  int getStateRaw(int button_id);
  bool isPressed(int button_id);
  bool isReleased(int button_id);
  void setCountMode(int button_id, int mode);
  unsigned long getCount(int button_id);
  void resetCount(int button_id);
  void loop(void);
};

#endif