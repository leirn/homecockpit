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
    2,
    3,
    4,
    5,
    6,
    8,
    10,
    11,
    12,
    13,
    14,
};

struct comm_pin_data
{
  int pin;
  String simconnect_event[3];
};

struct nav_pin_data
{
  int pin;
  String simconnect_event[4];
};

#define COMM_NAV_BUTTON_COUNT 12

const String SIMCONNECT_COMM_NAV[12] = {
    {0, {"NAV1_RADIO_SWAP", "NAV2_RADIO_SWAP", "NAV3_RADIO_SWAP", "NAV4_RADIO_SWAP"}},
    {2, {"NAV1_RADIO_WHOLE_INC", "NAV2_RADIO_WHOLE_INC", "NAV3_RADIO_WHOLE_INC", "NAV4_RADIO_WHOLE_INC"}},
    {3, {"NAV1_RADIO_WHOLE_DEC", "NAV2_RADIO_WHOLE_DEC", "NAV3_RADIO_WHOLE_DEC", "NAV4_RADIO_WHOLE_DEC"}},
    {4, {"NAV1_RADIO_FRACT_INC", "NAV2_RADIO_FRACT_INC", "NAV3_RADIO_FRACT_INC", "NAV4_RADIO_FRACT_INC"}},
    {5, {"NAV1_RADIO_FRACT_DEC", "NAV2_RADIO_FRACT_DEC", "NAV3_RADIO_FRACT_DEC", "NAV4_RADIO_FRACT_DEC"}},
    {6, {"NOT FOR USE", "NOT FOR USE", "NOT FOR USE", "NOT FOR USE"}},
    {8, {"COM1_RADIO_SWAP", "COM2_RADIO_SWAP", "COM3_RADIO_SWAP"}},
    {10, {"COM1_RADIO_WHOLE_INC", "COM2_RADIO_WHOLE_INC", "COM3_RADIO_WHOLE_INC"}},
    {11, {"COM1_RADIO_WHOLE_DEC", "COM2_RADIO_WHOLE_DEC", "COM3_RADIO_WHOLE_DEC"}},
    {12, {"COM1_RADIO_FRACT_INC", "COM2_RADIO_FRACT_INC", "COM3_RADIO_FRACT_INC"}},
    {13, {"COM1_RADIO_FRACT_DEC", "COM2_RADIO_FRACT_DEC", "COM3_RADIO_FRACT_DEC"}},
    {14, {"NOT FOR USE", "NOT FOR USE", "NOT FOR USE", "NOT FOR USE"}},
};

#define COMM_MENU_PIN 9
#define NAV_MENU_PIN 1
#define COMM_SELECT_PIN 14
#define NAV_SELECT_PIN 6

class comm_nav_unit
{
private:
  // Connection to MCP23S17
  Adafruit_MCP23X17 mcp;

  int active_comm, standby_comm, total_comm_number;
  int active_radio_nav, standby_radio_nav, total_nav_number;

  unsigned long debounceTime;
  unsigned long count[12];
  int countMode[12];
  int pressedState[12];   // the state when the button is considered pressed
  int unpressedState[12]; // the state when the button is considered unpressed

  int previousSteadyState[12];  // the previous steady state from the input pin, used to detect pressed and released event
  int lastSteadyState[12];      // the last steady state from the input pin
  int lastFlickerableState[12]; // the last flickerable state from the input pin

  unsigned long lastDebounceTime[12]; // the last time the output pin was toggled

  void selectNextStbyComm(void);     // Select the next standby COMM
  void selectNextStbyRadioNav(void); // Select the next standby RADIO NAV

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