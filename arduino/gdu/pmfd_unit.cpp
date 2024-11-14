#include "pmfd_unit.h"

pmfd_pin PMFD_PIN_DATA[PMFD_BUTTON_COUNT] = {
    {MCP00, 8, "G1000_PFD_GROUP_KNOB_INC", "G1000_MFD_GROUP_KNOB_INC"},
    {MCP00, 9, "G1000_PFD_GROUP_KNOB_DEC", "G1000_MFD_GROUP_KNOB_DEC"},
    {MCP00, 10, "G1000_PFD_PAGE_KNOB_INC", "G1000_MFD_PAGE_KNOB_INC"},
    {MCP00, 11, "G1000_PFD_PAGE_KNOB_DEC", "G1000_MFD_PAGE_KNOB_DEC"},
    {MCP00, 12, "G1000_PFD_CURSOR_BUTTON", "G1000_MFD_CURSOR_BUTTON"},
    {MCP01, 0, "G1000_PFD_DIRECTTO_BUTTON", "G1000_MFD_DIRECTTO_BUTTON"},
    {MCP01, 1, "G1000_PFD_ENTER_BUTTON", "G1000_MFD_ENTER_BUTTON"},
    {MCP01, 2, "G1000_PFD_MENU_BUTTON", "G1000_MFD_MENU_BUTTON"},
    {MCP01, 3, "G1000_PFD_PROCEDURE_BUTTON", "G1000_MFD_PROCEDURE_BUTTON"},
    {MCP01, 4, "G1000_PFD_FLIGHTPLAN_BUTTON", "G1000_MFD_FLIGHTPLAN_BUTTON"},
    {MCP01, 6, "G1000_PFD_CLEAR_BUTTON", "G1000_MFD_CLEAR_BUTTON"},
    {MCP01, 8, "G1000_PFD_MAP_UP", "G1000_PFD_MAP_UP"},        // Undefined yet
    {MCP01, 9, "G1000_PFD_MAP_DOWN", "G1000_PFD_MAP_DOWN"},    // Undefined yet
    {MCP01, 10, "G1000_PFD_MAP_LEFT", "G1000_PFD_MAP_LEFT"},   // Undefined yet
    {MCP01, 11, "G1000_PFD_MAP_RIGHT", "G1000_PFD_MAP_RIGHT"}, // Undefined yet
    {MCP01, 12, "G1000_PFD_ZOOMIN_BUTTON", "G1000_MFD_ZOOMIN_BUTTON"},
    {MCP01, 13, "G1000_PFD_ZOOMOUT_BUTTON", "G1000_MFD_ZOOMOUT_BUTTON"},
    {MCP01, 14, "G1000_PFD_MAP_PUSH", "G1000_PFD_MAP_ZOOM_OUT"}, // Undefined yet
};

pmfd_unit::pmfd_unit()
{
}

void pmfd_unit::begin(int cs_pin, int a_code)
{
  debounceTime = 0;

  if (!mcp00.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP00))
  {
    Serial.println("Error.");
    while (1)
      ;
  }

  if (!mcp01.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP01))
  {
    Serial.println("Error.");
    while (1)
      ;
  }

  active_gdu = PFD;

  // Set all buttons as inputs
  for (int i = 0; i < PMFD_BUTTON_COUNT; i++)
  {

    switch (PMFD_PIN_DATA[i].mcp_id)
    {
    case MCP00:
      mcp00.pinMode(PMFD_PIN_DATA[i].pin, INPUT_PULLUP);
      previousSteadyState[i] = mcp00.digitalRead(PMFD_PIN_DATA[i].pin);
      break;
    case MCP01:
      mcp01.pinMode(PMFD_PIN_DATA[i].pin, INPUT_PULLUP);
      previousSteadyState[i] = mcp01.digitalRead(PMFD_PIN_DATA[i].pin);
      break;
    }

    count[i] = 0;
    countMode[i] = COUNT_FALLING;

    pressedState[i] = LOW;
    unpressedState[i] = HIGH;

    lastSteadyState[i] = previousSteadyState[i];
    lastFlickerableState[i] = previousSteadyState[i];

    lastDebounceTime[i] = 0;
  }
}

void pmfd_unit::set_pfd(void)
{
  active_gdu = PFD;
  mcp00.digitalWrite(PFD_LED_PIN, LOW);
  mcp00.digitalWrite(MFD_LED_PIN, HIGH);
}

void pmfd_unit::set_mfd(void)
{
  active_gdu = MFD;
  mcp00.digitalWrite(PFD_LED_PIN, HIGH);
  mcp00.digitalWrite(MFD_LED_PIN, LOW);
}

void pmfd_unit::setDebounceTime(unsigned long time)
{
  debounceTime = time;
}

int pmfd_unit::getState(int button_id)
{
  return lastSteadyState[button_id];
}

int pmfd_unit::getStateRaw(int button_id)
{
  switch (PMFD_PIN_DATA[button_id].mcp_id)
  {
  case MCP00:
    return mcp00.digitalRead(PMFD_PIN_DATA[button_id].pin);
  case MCP01:
    return mcp01.digitalRead(PMFD_PIN_DATA[button_id].pin);
  }
  return -1;
}

bool pmfd_unit::isPressed(int button_id)
{
  if (previousSteadyState[button_id] == unpressedState[button_id] && lastSteadyState[button_id] == pressedState[button_id])
    return true;
  else
    return false;
}

bool pmfd_unit::isReleased(int button_id)
{
  if (previousSteadyState[button_id] == pressedState[button_id] && lastSteadyState[button_id] == unpressedState[button_id])
    return true;
  else
    return false;
}

String pmfd_unit::getSimconnectEvent(int button_id)
{
  if (active_gdu == PFD)
    return PMFD_PIN_DATA[button_id].simconnect_event_pfd;
  else
    return PMFD_PIN_DATA[button_id].simconnect_event_mfd;
}

void pmfd_unit::setCountMode(int button_id, int mode)
{
  countMode[button_id] = mode;
}

unsigned long pmfd_unit::getCount(int button_id)
{
  return count[button_id];
}

void pmfd_unit::resetCount(int button_id)
{
  count[button_id] = 0;
}

void pmfd_unit::loop(void)
{

  // Check first is change in PFD/MFD mode
  int pfd_state = mcp00.digitalRead(PFD_BUTTON_PIN);
  if (pfd_state == LOW)
  {
    set_pfd();
  }

  int mfd_state = mcp00.digitalRead(MFD_BUTTON_PIN);
  if (mfd_state == LOW)
  {
    set_mfd();
  }
  // read the state of the switch/button:
  uint16_t mcp_state = mcp00.readGPIOAB();
#ifdef DEBUG
  Serial.print("MCP 00 GPIO AB value :");
  Serial.print(mcp_state);
  Serial.println("");
#endif
  loop_state(MCP00, mcp_state);

  mcp_state = mcp01.readGPIOAB();
#ifdef DEBUG
  Serial.print("MCP 01 GPIO AB value :");
  Serial.print(mcp_state);
  Serial.println("");
#endif
  loop_state(MCP01, mcp_state);
}

void pmfd_unit::loop_state(int mcp, uint16_t mcp_state)
{

  for (int button_id = 0; button_id < PMFD_BUTTON_COUNT; button_id++)
  {
    if (PMFD_PIN_DATA[button_id].mcp_id != mcp)
      continue; // loop only on current MCP

    int currentState = (mcp_state >> PMFD_PIN_DATA[button_id].pin) & 1;

    unsigned long currentTime = millis();

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch/button changed, due to noise or pressing:
    if (currentState != lastFlickerableState[button_id])
    {
      // reset the debouncing timer
      lastDebounceTime[button_id] = currentTime;
      // save the the last flickerable state
      lastFlickerableState[button_id] = currentState;
    }

    if ((currentTime - lastDebounceTime[button_id]) >= debounceTime)
    {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // save the the steady state
      previousSteadyState[button_id] = lastSteadyState[button_id];
      lastSteadyState[button_id] = currentState;
    }

    if (previousSteadyState[button_id] != lastSteadyState[button_id])
    {
      if (countMode[button_id] == COUNT_BOTH)
        count[button_id]++;
      else if (countMode[button_id] == COUNT_FALLING)
      {
        if (previousSteadyState[button_id] == HIGH && lastSteadyState[button_id] == LOW)
          count[button_id]++;
      }
      else if (countMode[button_id] == COUNT_RISING)
      {
        if (previousSteadyState[button_id] == LOW && lastSteadyState[button_id] == HIGH)
          count[button_id]++;
      }
    }
  }
}