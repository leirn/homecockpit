#include "gdu_unit.h"

/**
 * @brief Default constructor for the gdu_unit class.
 *
 * This constructor initializes a new instance of the gdu_unit class.
 */
gdu_unit::gdu_unit()
{
}

/**
 * @brief Initializes the GDU unit.
 *
 * This function sets up the GDU unit by initializing the MCP object with the
 * specified chip select pin and address code. It also configures all buttons
 * as input with pull-up resistors and initializes their states and debounce
 * timers.
 *
 * @param cs_pin The chip select pin for the SPI communication.
 * @param a_code The address code for the MCP object.
 */
void gdu_unit::begin(int cs_pin, int a_code)
{
  debounceTime = 0;

  if (!mcp.begin_SPI(cs_pin, &SPI, a_code))
  {
    Serial.println("Error.");
    while (1)
      ;
  }

  // Set all buttons as inputs
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    mcp.pinMode(BUTTON_PINS[i], INPUT_PULLUP);

    count[i] = 0;
    countMode[i] = COUNT_FALLING;

    pressedState[i] = LOW;
    unpressedState[i] = HIGH;

    previousSteadyState[i] = mcp.digitalRead(BUTTON_PINS[i]);
    lastSteadyState[i] = previousSteadyState[i];
    lastFlickerableState[i] = previousSteadyState[i];

    lastDebounceTime[i] = 0;
  }
}

/**
 * @brief Sets the debounce time for the unit.
 *
 * This function sets the debounce time, which is the minimum time interval
 * that must pass before the unit can register another input. This helps to
 * prevent false or multiple triggers from occurring due to noise or rapid
 * switching.
 *
 * @param time The debounce time in milliseconds.
 */
void gdu_unit::setDebounceTime(unsigned long time)
{
  debounceTime = time;
}

int gdu_unit::getState(int button_id)
{
  return lastSteadyState[button_id];
}

int gdu_unit::getStateRaw(int button_id)
{
  return mcp.digitalRead(BUTTON_PINS[button_id]);
}

bool gdu_unit::isPressed(int button_id)
{
  if (previousSteadyState[button_id] == unpressedState[button_id] && lastSteadyState[button_id] == pressedState[button_id])
    return true;
  else
    return false;
}

bool gdu_unit::isReleased(int button_id)
{
  if (previousSteadyState[button_id] == pressedState[button_id] && lastSteadyState[button_id] == unpressedState[button_id])
    return true;
  else
    return false;
}

/**
 * @brief Retrieves the SimConnect event string based on the GDU type and button ID.
 *
 * @param gdu The type of GDU (Primary Flight Display or Multi-Function Display).
 * @param button_id The ID of the button for which the SimConnect event is requested.
 * @return String The SimConnect event string corresponding to the specified GDU type and button ID.
 */
String getSimconnectEvent(GDU_TYPE gdu, int button_id)
{
  if (gdu == PFD)
    return SIMCONNECT_PFD[button_id];
  else
    return SIMCONNECT_MFD[button_id];
}

void gdu_unit::setCountMode(int button_id, int mode)
{
  countMode[button_id] = mode;
}

unsigned long gdu_unit::getCount(int button_id)
{
  return count[button_id];
}

void gdu_unit::resetCount(int button_id)
{
  count[button_id] = 0;
}

/**
 * @brief Main loop function for the gdu_unit class.
 *
 * This function reads the state of the switches/buttons connected to the MCP23017 I/O expander,
 * debounces the inputs, and counts the button presses based on the configured counting mode.
 *
 * The function performs the following steps:
 * 1. Reads the state of the GPIO pins from the MCP23017.
 * 2. Iterates through each button and checks its current state.
 * 3. Debounces the button inputs by checking if the state has been stable for a specified debounce time.
 * 4. Updates the steady state of each button.
 * 5. Counts the button presses based on the configured counting mode (COUNT_BOTH, COUNT_FALLING, COUNT_RISING).
 *
 * The function uses the following member variables:
 * - mcp: An instance of the MCP23017 class used to read the GPIO pins.
 * - BUTTON_COUNT: The total number of buttons.
 * - BUTTON_PINS: An array of pin numbers corresponding to each button.
 * - lastFlickerableState: An array storing the last flickerable state of each button.
 * - lastDebounceTime: An array storing the last debounce time of each button.
 * - debounceTime: The debounce time in milliseconds.
 * - previousSteadyState: An array storing the previous steady state of each button.
 * - lastSteadyState: An array storing the last steady state of each button.
 * - countMode: An array storing the counting mode for each button.
 * - count: An array storing the count of button presses for each button.
 *
 * @note This function should be called repeatedly in the main loop of the Arduino sketch.
 */
void gdu_unit::loop(void)
{
  // read the state of the switch/button:
  uint16_t mcp_state = mcp.readGPIOAB();
#ifdef DEBUG
  Serial.print("GPIO AB value :");
  Serial.print(mcp_state);
  Serial.println("");
#endif

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