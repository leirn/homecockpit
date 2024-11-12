#include "comm_nav_unit.h"

comm_nav_unit::comm_nav_unit()
{
}

void comm_nav_unit::begin(int cs_pin, int a_code)
{
  debounceTime = 0;

  if (!mcp.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP00))
  {
    Serial.println("Error.");
    while (1)
      ;
  }

  // Set all buttons as inputs
  for (int i = 0; i < BUTTON_COUNT; i++)
  {

    mcp.pinMode(PIN_DATA[i].pin, INPUT_PULLUP);
    previousSteadyState[i] = mcp00.digitalRead(PIN_DATA[i].pin);

    count[i] = 0;
    countMode[i] = COUNT_FALLING;

    pressedState[i] = LOW;
    unpressedState[i] = HIGH;

    lastSteadyState[i] = previousSteadyState[i];
    lastFlickerableState[i] = previousSteadyState[i];

    lastDebounceTime[i] = 0;
  }
}

void comm_nav_unit::setDebounceTime(unsigned long time)
{
  debounceTime = time;
}

int comm_nav_unit::getState(int button_id)
{
  return lastSteadyState[button_id];
}

int comm_nav_unit::getStateRaw(int button_id)
{
  return mcp.digitalRead(BUTTON_PINS[button_id]);
}

bool comm_nav_unit::isPressed(int button_id)
{
  if (previousSteadyState[button_id] == unpressedState[button_id] && lastSteadyState[button_id] == pressedState[button_id])
    return true;
  else
    return false;
}

bool comm_nav_unit::isReleased(int button_id)
{
  if (previousSteadyState[button_id] == pressedState[button_id] && lastSteadyState[button_id] == unpressedState[button_id])
    return true;
  else
    return false;
}

String getSimconnectEvent(int button_id)
{
  return SIMCONNECT_COMM_NAV[button_id];
}

void comm_nav_unit::setCountMode(int button_id, int mode)
{
  countMode[button_id] = mode;
}

unsigned long comm_nav_unit::getCount(int button_id)
{
  return count[button_id];
}

void comm_nav_unit::resetCount(int button_id)
{
  count[button_id] = 0;
}

void comm_nav_unit::loop(void)
{
  // read the state of the switch/button:
  uint16_t mcp_state = mcp.readGPIOAB();

  for (int button_id = 0; button_id < BUTTON_COUNT; button_id++)
  {
    int currentState = (mcp_state >> BUTTON_PINS[button_id]) & 1;

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