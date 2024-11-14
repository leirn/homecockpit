/**
 * This class allows to interact with a PFD/MFD input module
 */

#ifndef pmfd_unit_h
#define pmfd_unit_h

#include <Arduino.h>

#include <Adafruit_MCP23X17.h>

#include "common.h"

#define COUNT_FALLING 0
#define COUNT_RISING 1
#define COUNT_BOTH 2

#define INPUT true
#define OUTPUT false

#define MCP00 0b00
#define MCP01 0b01

#define PFD_BUTTON_PIN 0
#define MFD_BUTTON_PIN 1
#define PFD_LED_PIN 2
#define MFD_LED_PIN 3

struct pmfd_pin
{
  int mcp_id;
  int pin;
  String simconnect_event_pfd;
  String simconnect_event_mfd;
};

enum PMFD_PINS
{
  GROUP_LEFT,
  GROUP_RIGHT,
  PAGE_LEFT,
  PAGE_RIGHT,
  PAGE_PUSH,
  DIRECT_TO,
  ENTER,
  MENU,
  PROC,
  FPL,
  CLEAR,
  MAP_UP,
  MAP_DOWN,
  MAP_LEFT,
  MAP_RIGHT,
  MAP_ZOOM_IN,
  MAP_ZOOM_OUT,
  MAP_PUSH,

};

#define PMFD_BUTTON_COUNT 18

class pmfd_unit
{
private:
  // Connection to MCP23S17
  Adafruit_MCP23X17 mcp00;
  Adafruit_MCP23X17 mcp01;

  // ACTIVE_GDU
  GDU_TYPE active_gdu;

  unsigned long debounceTime;
  unsigned long count[PMFD_BUTTON_COUNT];
  int countMode[PMFD_BUTTON_COUNT];
  int pressedState[PMFD_BUTTON_COUNT];   // the state when the button is considered pressed
  int unpressedState[PMFD_BUTTON_COUNT]; // the state when the button is considered unpressed

  int previousSteadyState[PMFD_BUTTON_COUNT];  // the previous steady state from the input pin, used to detect pressed and released event
  int lastSteadyState[PMFD_BUTTON_COUNT];      // the last steady state from the input pin
  int lastFlickerableState[PMFD_BUTTON_COUNT]; // the last flickerable state from the input pin

  unsigned long lastDebounceTime[PMFD_BUTTON_COUNT]; // the last time the output pin was toggled

  void loop_state(int mcp, uint16_t mcp_state); // loop a particular MCP

  void set_pfd(void); // Set device in PFD mode
  void set_mfd(void); // Set device in MFD mode

public:
  pmfd_unit();
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