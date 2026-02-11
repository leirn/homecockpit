#ifndef softkey_h
#define softkey_h

#include <Arduino.h>

#include <Joystick.h>

#include <Adafruit_MCP23X17.h>

#define SOFTKEY_BUTTON_COUNT 12

class softkey {
  public:
    softkey();
    void begin(int pin);
    bool isPressed();

  private:
    int _pin;
    Joystick_ Joystick;
    Adafruit_MCP23X17 mcp;
};

#endif