#include "ap_unit.h"

ap_unit::ap_unit() {
}


void ap_unit::begin(int cs_pin, int a_code) {
	debounceTime = 0;

  if (!mcp00.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP00)) {
    Serial.println("Error.");
    while (1);
  }

  if (!mcp01.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP01)) {
    Serial.println("Error.");
    while (1);
  }

  if (!mcp10.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP10)) {
    Serial.println("Error.");
    while (1);
  }

  if (!mcp11.begin_SPI(cs_pin, &SPI, (a_code & 0b100) | MCP11)) {
    Serial.println("Error.");
    while (1);
  }

  // Set all buttons as inputs
  for(int i = 0; i < BUTTON_COUNT; i++) {
    
    switch(PIN_DATA[i].mcp_id) {
      case MCP00:
        mcp00.pinMode(PIN_DATA[i].pin, INPUT_PULLUP);
        previousSteadyState[i] = mcp00.digitalRead(PIN_DATA[i].pin);
        break;
      case MCP01:
        mcp01.pinMode(PIN_DATA[i].pin, INPUT_PULLUP);
        previousSteadyState[i] = mcp01.digitalRead(PIN_DATA[i].pin);
        break;
      case MCP10:
        mcp10.pinMode(PIN_DATA[i].pin, INPUT_PULLUP);
        previousSteadyState[i] = mcp10.digitalRead(PIN_DATA[i].pin);
        break;
      case MCP11:
        mcp11.pinMode(PIN_DATA[i].pin, INPUT_PULLUP);
        previousSteadyState[i] = mcp11.digitalRead(PIN_DATA[i].pin);
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

void ap_unit::setDebounceTime(unsigned long time) {
  debounceTime = time;
}


int ap_unit::getState(int button_id) {
	return lastSteadyState[button_id];
}

int ap_unit::getStateRaw(int button_id) {
  switch(PIN_DATA[button_id].mcp_id) {
    case MCP00:
      return mcp00.digitalRead(PIN_DATA[button_id].pin);
    case MCP01:
      return mcp01.digitalRead(PIN_DATA[button_id].pin);
    case MCP10:
      return mcp10.digitalRead(PIN_DATA[button_id].pin);
    case MCP11:
      return mcp11.digitalRead(PIN_DATA[button_id].pin);
  }
	return -1;
}

bool ap_unit::isPressed(int button_id) {
	if(previousSteadyState[button_id] == unpressedState[button_id] && lastSteadyState[button_id] == pressedState[button_id])
		return true;
	else
		return false;
}

bool ap_unit::isReleased(int button_id) {
	if(previousSteadyState[button_id] == pressedState[button_id] && lastSteadyState[button_id] == unpressedState[button_id])
		return true;
	else
		return false;
}

void ap_unit::setCountMode(int button_id, int mode) {
	countMode[button_id] = mode;
}

unsigned long ap_unit::getCount(int button_id) {
	return count[button_id];
}

void ap_unit::resetCount(int button_id) {
	count[button_id] = 0;
}

void ap_unit::loop(void) {
	// read the state of the switch/button:
  uint16_t mcp_state = mcp00.readGPIOAB();
#ifdef DEBUG
  Serial.print("MCP 00 GPIO AB value :");
  Serial.print(mcp_state);
  Serial.println("");
#endif
  loop_state(MCP00, mcp_state);
}

void ap_unit::loop_state(int mcp, uint16_t mcp_state) {

  for(int button_id = 0; button_id < BUTTON_COUNT; button_id++) {
    if(PIN_DATA[button_id].mcp_id != mcp) continue; // loop only on current MCP

    int currentState = (mcp_state >> PIN_DATA[button_id].pin) & 1;

    unsigned long currentTime = millis();

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch/button changed, due to noise or pressing:
    if (currentState != lastFlickerableState[button_id]) {
      // reset the debouncing timer
      lastDebounceTime[button_id] = currentTime;
      // save the the last flickerable state
      lastFlickerableState[button_id] = currentState;
    }

    if ((currentTime - lastDebounceTime[button_id]) >= debounceTime) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // save the the steady state
      previousSteadyState[button_id] = lastSteadyState[button_id];
      lastSteadyState[button_id] = currentState;
    }

    if(previousSteadyState[button_id] != lastSteadyState[button_id]){
      if(countMode[button_id] == COUNT_BOTH)
        count[button_id]++;
      else if(countMode[button_id] == COUNT_FALLING){
        if(previousSteadyState[button_id] == HIGH && lastSteadyState[button_id] == LOW)
          count[button_id]++;
      }
      else if(countMode[button_id] == COUNT_RISING){
        if(previousSteadyState[button_id] == LOW && lastSteadyState[button_id] == HIGH)
          count[button_id]++;
      }
    }
  }
}