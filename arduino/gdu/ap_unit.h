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

struct ap_pin
{
  int mcp_id;
  int pin;
  bool in_out; // True if input (BUTTON), False if output (LED)
  String simconnect_event;
};

enum AP_PINS
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

class ap_unit
{
private:
  // Connection to MCP23S17
  Adafruit_MCP23X17 mcp00;
  Adafruit_MCP23X17 mcp01;
  Adafruit_MCP23X17 mcp10;
  Adafruit_MCP23X17 mcp11;

  unsigned long debounceTime;
  unsigned long count[AP_BUTTON_COUNT];
  int countMode[AP_BUTTON_COUNT];
  int pressedState[AP_BUTTON_COUNT];   // the state when the button is considered pressed
  int unpressedState[AP_BUTTON_COUNT]; // the state when the button is considered unpressed

  int previousSteadyState[AP_BUTTON_COUNT];  // the previous steady state from the input pin, used to detect pressed and released event
  int lastSteadyState[AP_BUTTON_COUNT];      // the last steady state from the input pin
  int lastFlickerableState[AP_BUTTON_COUNT]; // the last flickerable state from the input pin

  unsigned long lastDebounceTime[AP_BUTTON_COUNT]; // the last time the output pin was toggled

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