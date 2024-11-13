#include "comm_nav_unit.h"

comm_nav_unit::comm_nav_unit()
{
  active_comm = 0;
  standby_comm = 1;
  total_comm_number = 2;
  active_radio_nav = 0;
  standby_radio_nav = 1;
  total_nav_number = 2;
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
  if (button_id == COMM_SELECT_PIN)
  {
    return "COM_RADIO SELECT_" + (active_comm + 1);
  }
  if (button_id == NAV_SELECT_PIN)
  {
    return "NAV_RADIO SELECT_" + (active_radio_nav + 1);
  }
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

/**
 * @brief Selects the next standby communication channel.
 *
 * This function updates the standby communication channel based on the current
 * active and standby communication channels. The selection follows these rules:
 * - If the current standby channel is COMM1:
 *   - If the active channel is COMM2, the standby channel is set to COMM3.
 *   - Otherwise, the standby channel is set to COMM2.
 * - If the current standby channel is COMM2:
 *   - If the active channel is COMM3, the standby channel is set to COMM1.
 *   - Otherwise, the standby channel is set to COMM3.
 * - If the current standby channel is neither COMM1 nor COMM2:
 *   - If the active channel is COMM1, the standby channel is set to COMM2.
 *   - Otherwise, the standby channel is set to COMM1.
 */
void comm_nav_unit::selectNextStbyComm(void)
{
  standby_comm = (standby_comm + 1) % total_comm_number;
  if (standby_comm == active_comm)
    standby_comm = (standby_comm + 1) % total_comm_number;
}

/**
 * @brief Selects the next standby radio navigation unit.
 *
 * This function cycles through the available standby radio navigation units
 * (NAV1, NAV2, NAV3, NAV4, DME1, DME2, ADF, TACAN1, TACAN2) and selects the next one
 * in the sequence. If the next unit in the sequence is currently the active radio
 * navigation unit, it skips to the following unit.
 *
 * The sequence is as follows:
 * NAV1 -> NAV2 -> NAV3 -> NAV4 -> DME1 -> DME2 -> ADF -> TACAN1 -> TACAN2 -> NAV1
 *
 * If the next unit in the sequence is the active radio navigation unit, the function
 * will select the unit after the active one.
 */
void comm_nav_unit::selectNextStbyRadioNav(void)
{
  standby_radio_nav = (standby_radio_nav + 1) % total_nav_number;
  if (standby_radio_nav == standby_radio_nav)
    standby_radio_nav = (standby_radio_nav + 1) % total_nav_number;
}

void comm_nav_unit::loop(void)
{
  // read the state of the switch/button:
  uint16_t mcp_state = mcp.readGPIOAB();

  // Check if COM menu button has been pressed
  int comm_menu_state = (mcp_state >> COMM_MENU_PIN) & 1;
  if (comm_menu_state == LOW)
  {
    selectNextStbyComm();
  }

  // Check if NAV menu button has been pressed
  int nav_menu_state = (mcp_state >> NAV_MENU_PIN) & 1;
  if (nav_menu_state == LOW)
  {
    selectNextStbyRadioNav();
  }

  // Check if COM select button has been pressed
  int comm_menu_state = (mcp_state >> COMM_SELECT_PIN) & 1;
  if (comm_menu_state == LOW)
  {
    selectNextStbyComm();
  }

  // Check if NAV select button has been pressed
  int nav_menu_state = (mcp_state >> NAV_SELECT_PIN) & 1;
  if (nav_menu_state == LOW)
  {
    selectNextStbyRadioNav();
  }

  for (int button_id = 0; button_id < COMM_NAV_BUTTON_COUNT; button_id++)
  {

    int currentState = (mcp_state >> COMM_NAV_BUTTON_COUNT[button_id].pin) & 1;

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