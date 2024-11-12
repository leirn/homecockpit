/**
 * This class allows to interact with a AUTO PILOT module
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
    {MCP00, 0, INPUT, "HDG"},
    {MCP00, 1, INPUT, "HDG_LED"},
    {MCP00, 2, INPUT, "APPR"},
    {MCP00, 3, INPUT, "APPR_LED"},
    {MCP00, 4, INPUT, "NAV"},
    {MCP00, 5, INPUT, "NAV_LED"},
    {MCP00, 8, INPUT, "HDG_BUG_PUSH"},
    {MCP00, 9, INPUT, "HDG_BUG_LEFT"},
    {MCP00, 10, INPUT, "HDG_BUG_RIGHT"},
    {MCP00, 11, INPUT, "BC"},
    {MCP00, 12, INPUT, "BC_LED"},
    {MCP00, 13, INPUT, "CRS1_BUG_PUSH"},
    {MCP00, 14, INPUT, "CRS1_BUG_LEFT"},
    {MCP00, 15, INPUT, "CRS1_BUG_RIGHT"},
    {MCP01, 0, INPUT, "ALT_BUG_PUSH"},
    {MCP01, 1, INPUT, "ALT_BUG_INNER_LEFT"},
    {MCP01, 2, INPUT, "ALT_BUG_INNER_RIGHT"},
    {MCP01, 3, INPUT, "ALT_BUG_OUTTER_LEFT"},
    {MCP01, 4, INPUT, "ALT_BUG_OUTTER_RIGHT"},
    {MCP01, 6, INPUT, "ALT"},
    {MCP01, 7, INPUT, "ALT_LED"},
    {MCP01, 8, INPUT, "VS"},
    {MCP01, 9, INPUT, "VS_LED"},
    {MCP01, 10, INPUT, "VNV"},
    {MCP01, 11, INPUT, "VNV_LED"},
    {MCP01, 12, INPUT, "NOSE_UP"},
    {MCP01, 13, INPUT, "NOSE_DOWN"},
    {MCP10, 0, INPUT, "AP"},
    {MCP10, 1, INPUT, "A¨P_LED"},
    {MCP10, 2, INPUT, "BANK"},
    {MCP10, 3, INPUT, "BANK_LED"},
    {MCP10, 4, INPUT, "FD"},
    {MCP10, 5, INPUT, "FD_LED"},
    {MCP10, 6, INPUT, "AUTO_THROTTLE"},
    {MCP10, 7, INPUT, "AUTO_THROTTLE_LED"},
    {MCP10, 8, INPUT, "YAW_DAMPER"},
    {MCP10, 9, INPUT, "YAW_DAMPER_LED"},
    {MCP10, 10, INPUT, "CRS2_BUG_PUSH"},
    {MCP10, 11, INPUT, "CRS2_BUG_LEFT"},
    {MCP10, 12, INPUT, "CRS2_BUG_RIGHT"},
    {MCP10, 13, INPUT, "BARO_LEFT"},
    {MCP10, 14, INPUT, "BARO_RIGHT"},
    {MCP11, 0, INPUT, "IAS"},
    {MCP11, 6, INPUT, "IAS_LED"},
    {MCP11, 1, INPUT, "SPEED_BUG_PUSH"},
    {MCP11, 2, INPUT, "SPEED_BUG_LEFT"},
    {MCP11, 3, INPUT, "SPEED_BUG_RIGHT"},
    {MCP11, 4, INPUT, "FLC"},
    {MCP11, 5, INPUT, "FLC_LED"},
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