/**
 * This class allows to interact with a AUTO PILOT module
 *
 * An AP uses 4 MCP23S17, which addresses are: x00, x01, x10, x11.
 * Therefore, the .begin() method muse take a parameter that must be 0b1xx or 0b0xx (the last two digits are ignored).
 *
 */

#ifndef ap_unit_h
#define ap_unit_h

#include <Arduino.h>

#include <Adafruit_MCP23X17.h>

#define COUNT_FALLING 0
#define COUNT_RISING 1
#define COUNT_BOTH 2

#define INPUT true
#define OUTPUT false

#define MCP00 0b00
#define MCP01 0b01
#define MCP10 0b10
#define MCP11 0b11

struct ap_pin_data
{
  int mcp_id;
  int pin;
  bool in_out; // True if input (BUTTON), False if output (LED)
  String simconnect_event;
};

enum PINS
{
  HDG,
  HDG_LED,
  APPR,
  APPR_LED,
  NAV,
  NAV_LED,
  HDG_BUG_PUSH,
  HDG_BUG_LEFT,
  HDG_BUG_RIGHT,
  BC,
  BC_LED,
  CRS1_BUG_PUSH,
  CRS1_BUG_LEFT,
  CRS1_BUG_RIGHT,
  ALT_BUG_PUSH,
  ALT_BUG_INNER_LEFT,
  ALT_BUG_INNER_RIGHT,
  ALT_BUG_OUTTER_LEFT,
  ALT_BUG_OUTTER_RIGHT,
  ALT,
  ALT_LED,
  VS,
  VS_LED,
  VNV,
  VNV_LED,
  NOSE_UP,
  NOSE_DOWN,
  AP,
  AP_LED,
  BANK,
  BANK_LED,
  FD,
  FD_LED,
  AUTO_THROTTLE,
  AUTO_THROTTLE_LED,
  YAW_DAMPER,
  YAW_DAMPER_LED,
  CRS2_BUG_PUSH,
  CRS2_BUG_LEFT,
  CRS2_BUG_RIGHT,
  BARO_KEFT,
  BARO_RIGHT,
  IAS,
  IAS_LED,
  SPEED_BUG_PUSH,
  SPEED_BUG_LEFT,
  SPEED_BUG_RIGHT,
  FLC,
  FLC_LED,
};

#define AP_BUTTON_COUNT 49

ap_pin_data PIN_DATA[AP_BUTTON_COUNT] = {
    {MCP00, 0, INPUT, "AP_HDG_HOLD"},
    {MCP00, 1, INPUT, "AP_HDG_HOLD_LED"},
    {MCP00, 2, INPUT, "AP_APR_HOLD"},
    {MCP00, 3, INPUT, "AP_APR_HOLD_LED"},
    {MCP00, 4, INPUT, "AP_NAV1_HOLD"},
    {MCP00, 5, INPUT, "AP_NAV1_HOLD_LED"},
    {MCP00, 8, INPUT, "HEADING_BUG_SET"}, // Must take current heading as parameter
    {MCP00, 9, INPUT, "HEADING_BUG_INC"},
    {MCP00, 10, INPUT, "HEADING_BUG_DEC"},
    {MCP00, 11, INPUT, "AP_BC_HOLD"},
    {MCP00, 12, INPUT, "AP_BC_HOLD_LED"},
    {MCP00, 13, INPUT, "VOR1_SET"}, // Will take current VOR bearing as a parameter
    {MCP00, 14, INPUT, "VOR1_OBI_INC"},
    {MCP00, 15, INPUT, "VOR1_OBI_DEC"},
    {MCP01, 0, INPUT, "ALT_BUG_PUSH"}, // Undefined yet
    {MCP01, 1, INPUT, "AP_ALT_VAR_DEC"},
    {MCP01, 2, INPUT, "AP_ALT_VAR_INC"},
    {MCP01, 3, INPUT, "ALT_BUG_OUTTER_LEFT"},  // Undefined yet
    {MCP01, 4, INPUT, "ALT_BUG_OUTTER_RIGHT"}, // Undefined yet
    {MCP01, 6, INPUT, "AP_ALT_HOLD"},
    {MCP01, 7, INPUT, "AP_ALT_HOLD_LED"},
    {MCP01, 8, INPUT, "AP_PANEL_VS_HOLD"},
    {MCP01, 9, INPUT, "AP_PANEL_VS_HOLD_LED"},
    {MCP01, 10, INPUT, "VNV"},       // Undefined yet
    {MCP01, 11, INPUT, "VNV_LED"},   // Undefined yet
    {MCP01, 12, INPUT, "NOSE_UP"},   // Undefined yet
    {MCP01, 13, INPUT, "NOSE_DOWN"}, // Undefined yet
    {MCP10, 0, INPUT, "AP_MASTER"},
    {MCP10, 1, INPUT, "AP_MASTER_LED"},
    {MCP10, 2, INPUT, "AP_BANK_HOLD"},
    {MCP10, 3, INPUT, "AP_BANK_HOLD_LED"},
    {MCP10, 4, INPUT, "TOGGLE_FLIGHT_DIRECTOR"},
    {MCP10, 5, INPUT, "TOGGLE_FLIGHT_DIRECTOR_LED"},
    {MCP10, 6, INPUT, "AUTO_THROTTLE"},
    {MCP10, 7, INPUT, "AUTO_THROTTLE_LED"},
    {MCP10, 8, INPUT, "YAW_DAMPER_TOGGLE"},
    {MCP10, 9, INPUT, "YAW_DAMPER_TOGGLE_LED"},
    {MCP10, 10, INPUT, "VOR2_SET"}, // Will take current VOR bearing as a parameter
    {MCP10, 11, INPUT, "VOR2_OBI_INC"},
    {MCP10, 12, INPUT, "VOR2_OBI_DEC"},
    {MCP10, 13, INPUT, "BARO_LEFT"},  // Undefined yet
    {MCP10, 14, INPUT, "BARO_RIGHT"}, // Undefined yet
    {MCP11, 0, INPUT, "AP_AIRSPEED_ON"},
    {MCP11, 6, INPUT, "AP_AIRSPEED_ON_LED"},
    {MCP11, 1, INPUT, "SPEED_BUG_PUSH"}, // Undefined yet
    {MCP11, 2, INPUT, "AP_SPD_VAR_INC"},
    {MCP11, 3, INPUT, "AP_SPD_VAR_DEC"},
    {MCP11, 4, INPUT, "FLIGHT_LEVEL_CHANGE"},
    {MCP11, 5, INPUT, "FLIGHT_LEVEL_CHANGE_LED"},
};

class ap_unit
{
private:
  // Connection to MCP23S17
  Adafruit_MCP23X17 mcp00;
  Adafruit_MCP23X17 mcp01;
  Adafruit_MCP23X17 mcp10;
  Adafruit_MCP23X17 mcp11;

  unsigned long debounceTime;
  unsigned long count[12];
  int countMode[12];
  int pressedState[12];   // the state when the button is considered pressed
  int unpressedState[12]; // the state when the button is considered unpressed

  int previousSteadyState[12];  // the previous steady state from the input pin, used to detect pressed and released event
  int lastSteadyState[12];      // the last steady state from the input pin
  int lastFlickerableState[12]; // the last flickerable state from the input pin

  unsigned long lastDebounceTime[12]; // the last time the output pin was toggled

  void loop_state(int mcp, uint16_t mcp_state); // loop a particular MCP

public:
  ap_unit();
  void begin(int cs_pin, int a_code);
  void setDebounceTime(unsigned long time);
  int getState(int button_id);
  int getStateRaw(int button_id);
  bool isPressed(int button_id);
  bool isReleased(int button_id);
  String getSimconnectEvent(int button_id);
  void setCountMode(int button_id, int mode);
  unsigned long getCount(int button_id);
  void resetCount(int button_id);
  void loop(void);
};

#endif