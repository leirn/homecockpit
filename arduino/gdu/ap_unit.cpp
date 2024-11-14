#include "ap_unit.h"

ap_pin AP_PIN_DATA[AP_BUTTON_COUNT] = {
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
    {MCP01, 12, INPUT, "AP_VS_VAR_INC"},
    {MCP01, 13, INPUT, "AP_VS_VAR_DEC"},
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
    {MCP10, 13, INPUT, "KOHLSMAN_INC"},
    {MCP10, 14, INPUT, "KOHLSMAN_DEC"},
    {MCP11, 0, INPUT, "AP_AIRSPEED_ON"},
    {MCP11, 6, INPUT, "AP_AIRSPEED_ON_LED"},
    {MCP11, 1, INPUT, "SPEED_BUG_PUSH"}, // Undefined yet. CHange from IAS to Mach ?
    {MCP11, 2, INPUT, "AP_SPD_VAR_INC"},
    {MCP11, 3, INPUT, "AP_SPD_VAR_DEC"},
    {MCP11, 4, INPUT, "FLIGHT_LEVEL_CHANGE"},
    {MCP11, 5, INPUT, "FLIGHT_LEVEL_CHANGE_LED"},
};


ap_unit::ap_unit()
{
}

void ap_unit::begin(int cs_pin, int a_code)
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

  if (!mcp10.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP10))
  {
    Serial.println("Error.");
    while (1)
      ;
  }

  if (!mcp11.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP11))
  {
    Serial.println("Error.");
    while (1)
      ;
  }

  // Set all buttons as inputs
  for (int i = 0; i < AP_BUTTON_COUNT; i++)
  {

    switch (AP_PIN_DATA[i].mcp_id)
    {
    case MCP00:
      mcp00.pinMode(AP_PIN_DATA[i].pin, INPUT_PULLUP);
      previousSteadyState[i] = mcp00.digitalRead(AP_PIN_DATA[i].pin);
      break;
    case MCP01:
      mcp01.pinMode(AP_PIN_DATA[i].pin, INPUT_PULLUP);
      previousSteadyState[i] = mcp01.digitalRead(AP_PIN_DATA[i].pin);
      break;
    case MCP10:
      mcp10.pinMode(AP_PIN_DATA[i].pin, INPUT_PULLUP);
      previousSteadyState[i] = mcp10.digitalRead(AP_PIN_DATA[i].pin);
      break;
    case MCP11:
      mcp11.pinMode(AP_PIN_DATA[i].pin, INPUT_PULLUP);
      previousSteadyState[i] = mcp11.digitalRead(AP_PIN_DATA[i].pin);
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

void ap_unit::setDebounceTime(unsigned long time)
{
  debounceTime = time;
}

int ap_unit::getState(int button_id)
{
  return lastSteadyState[button_id];
}

int ap_unit::getStateRaw(int button_id)
{
  switch (AP_PIN_DATA[button_id].mcp_id)
  {
  case MCP00:
    return mcp00.digitalRead(AP_PIN_DATA[button_id].pin);
  case MCP01:
    return mcp01.digitalRead(AP_PIN_DATA[button_id].pin);
  case MCP10:
    return mcp10.digitalRead(AP_PIN_DATA[button_id].pin);
  case MCP11:
    return mcp11.digitalRead(AP_PIN_DATA[button_id].pin);
  }
  return -1;
}

bool ap_unit::isPressed(int button_id)
{
  if (previousSteadyState[button_id] == unpressedState[button_id] && lastSteadyState[button_id] == pressedState[button_id])
    return true;
  else
    return false;
}

bool ap_unit::isReleased(int button_id)
{
  if (previousSteadyState[button_id] == pressedState[button_id] && lastSteadyState[button_id] == unpressedState[button_id])
    return true;
  else
    return false;
}

String ap_unit::getSimconnectEvent(int button_id)
{
  return AP_PIN_DATA[button_id].simconnect_event;
}

void ap_unit::setCountMode(int button_id, int mode)
{
  countMode[button_id] = mode;
}

unsigned long ap_unit::getCount(int button_id)
{
  return count[button_id];
}

void ap_unit::resetCount(int button_id)
{
  count[button_id] = 0;
}

void ap_unit::loop(void)
{
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
  loop_state(MCP00, mcp_state);

  mcp_state = mcp10.readGPIOAB();
#ifdef DEBUG
  Serial.print("MCP 10 GPIO AB value :");
  Serial.print(mcp_state);
  Serial.println("");
#endif
  loop_state(MCP10, mcp_state);

  mcp_state = mcp11.readGPIOAB();
#ifdef DEBUG
  Serial.print("MCP 11 GPIO AB value :");
  Serial.print(mcp_state);
  Serial.println("");
#endif
  loop_state(MCP11, mcp_state);
}

void ap_unit::loop_state(int mcp, uint16_t mcp_state)
{

  for (int button_id = 0; button_id < AP_BUTTON_COUNT; button_id++)
  {
    if (AP_PIN_DATA[button_id].mcp_id != mcp)
      continue; // loop only on current MCP

    int currentState = (mcp_state >> AP_PIN_DATA[button_id].pin) & 1;

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