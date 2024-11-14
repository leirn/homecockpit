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

struct comm_nav_pin_data
{
  int pin;
  String simconnect_event[4];
};

#define COMM_NAV_BUTTON_COUNT 12

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
  unsigned long count[COMM_NAV_BUTTON_COUNT];
  int countMode[COMM_NAV_BUTTON_COUNT];
  int pressedState[COMM_NAV_BUTTON_COUNT];   // the state when the button is considered pressed
  int unpressedState[COMM_NAV_BUTTON_COUNT]; // the state when the button is considered unpressed

  int previousSteadyState[COMM_NAV_BUTTON_COUNT];  // the previous steady state from the input pin, used to detect pressed and released event
  int lastSteadyState[COMM_NAV_BUTTON_COUNT];      // the last steady state from the input pin
  int lastFlickerableState[COMM_NAV_BUTTON_COUNT]; // the last flickerable state from the input pin

  unsigned long lastDebounceTime[COMM_NAV_BUTTON_COUNT]; // the last time the output pin was toggled

  void selectNextStbyComm(void);     // Select the next standby COMM
  void selectNextStbyRadioNav(void); // Select the next standby RADIO NAV

public:
  comm_nav_unit();
  void begin(int cs_pin, int a_code);
  void setDebounceTime(unsigned long time);
  int getState(int button_id);
  int getStateRaw(int button_id);
  bool isPressed(int button_id);
  bool isReleased(int button_id);
  String comm_nav_unit::getSimconnectEvent(int button_id);
  void setCountMode(int button_id, int mode);
  unsigned long getCount(int button_id);
  void resetCount(int button_id);
  void loop(void);
};

#endif