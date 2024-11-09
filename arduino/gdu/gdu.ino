#include "gdu_unit.h"

#define PFD 1
#define MFD 1

#define PFD_CS_PIN 53
#define MFD_CS_PIN 53

#define PFD_A_CODE 0
#define MFD_A_CODE 1

#ifdef PFD
gdu_unit pfd;
#endif
#ifdef MFD
gdu_unit mfd;
#endif

void setup() {
  Serial.begin(9600);
  while (!Serial);

#ifdef PFD
  pfd.begin(PFD_CS_PIN, PFD_A_CODE);
#endif
#ifdef MFD
  mfd.begin(MFD_CS_PIN, MFD_A_CODE);
#endif

}

void loop() {
#ifdef PFD
  pfd.loop();

  for(int i = 0; i < BUTTON_COUNT; ++i) {
    if (pfd.isPressed(i)) {
      Serial.print("PFD Button ");
      Serial.print(i);
      Serial.println(" is pressed");
    }
  }
#endif
#ifdef MFD
  mfd.loop();

  for(int i = 0; i < BUTTON_COUNT; ++i) {
    if (mfd.isPressed(i)) {
      Serial.print("MFD Button ");
      Serial.print(i);
      Serial.println(" is pressed");
    }
  }
#endif
}