#include "softkey.h"

Joystick_ Joystick = Joystick_(
  0x03, // HID type (0x03 for Joystick, 0x04 for Gamepad)
  JOYSTICK_TYPE_JOYSTICK, // Joystick type (0x00 for Joystick, 0x01 for Gamepad)
  SOFTKEY_BUTTON_COUNT, // Button Count
  0, // Hat Switch Count
  false, // X Axis
  false, // Y Axis 
  false, // Z Axis
  false, // Rx Axis
  false, // Ry Axis
  false, // Rz Axis
  false, // rudder
  false, // throttle
  false, // accelerator
  false, // brake
  false // steering
);

void softkey::softkey() {
  Joystick.begin();
}