/**
 * This class allows to interact with a PFD/MFD input module
 */

#ifndef pmfd_unit_h
#define pmfd_unit_h

#include <Arduino.h>

#include <Adafruit_MCP23X17.h>

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

struct pmfd_pin_data
{
  int mcp_id;
  int pin;
  String simconnect_event_pfd;
  String simconnect_event_mfd;
};

enum PINS
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

ap_pin_data PIN_DATA[PMFD_BUTTON_COUNT] = {
    {MCP00, 8, "G1000_PFD_GROUP_LEFT", "G1000_MFD_GROUP_LEFT"},
    {MCP00, 9, "G1000_PFD_GROUP_RIGHT", "G1000_PFD_GROUP_RIGHT"},
    {MCP00, 10, "G1000_PFD_PAGE_LEFT", "G1000_PFD_PAGE_LEFT"},
    {MCP00, 11, "G1000_PFD_PAGE_RIGHT", "G1000_PFD_PAGE_RIGHT"},
    {MCP00, 12, "G1000_PFD_PAGE_PUSH", "G1000_PFD_PAGE_PUSH"},
    {MCP01, 0, "G1000_PFD_DIRECT_TO", "G1000_PFD_DIRECT_TO"},
    {MCP01, 1, "G1000_PFD_ENTER", "G1000_PFD_ENTER"},
    {MCP01, 2, "G1000_PFD_MENU", "G1000_PFD_MENU"},
    {MCP01, 3, "G1000_PFD_PROC", "G1000_PFD_PROC"},
    {MCP01, 4, "G1000_PFD_FPL", "G1000_PFD_FPL"},
    {MCP01, 6, "G1000_PFD_CLEAR", "G1000_PFD_CLEAR"},
    {MCP01, 8, "G1000_PFD_MAP_UP", "G1000_PFD_MAP_UP"},
    {MCP01, 9, "G1000_PFD_MAP_DOWN", "G1000_PFD_MAP_DOWN"},
    {MCP01, 10, "G1000_PFD_MAP_LEFT", "G1000_PFD_MAP_LEFT"},
    {MCP01, 11, "G1000_PFD_MAP_RIGHT", "G1000_PFD_MAP_RIGHT"},
    {MCP01, 12, "G1000_PFD_MAP_ZOOM_IN", "G1000_PFD_MAP_ZOOM_IN"},
    {MCP01, 13, "G1000_PFD_MAP_ZOOM_OUT"},
    {MCP01, 14, "G1000_PFD_MAP_PUSH", "G1000_PFD_MAP_ZOOM_OUT"},
};

enum ACTIVE_GDU
{
  PFD,
  MFD,
};

class pmfd_unit
{
private:
  // Connection to MCP23S17
  Adafruit_MCP23X17 mcp00;
  Adafruit_MCP23X17 mcp01;

  // ACTIVE_GDU
  ACTIVE_GDU active_gdu;

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

  void set_pfd(void); // Set device in PFD mode
  void set_mfd(void); // Set device in MFD mode

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