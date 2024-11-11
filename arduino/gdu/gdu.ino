#include "gdu_unit.h"

#define PFD 1
//#define MFD 1

#define PFD_CS_PIN 53
#define MFD_CS_PIN 53
#define AP_CS_PIN 53

#define PFD_A_CODE 0
#define MFD_A_CODE 1
#define AP_A_CODE 0b100

#define DEBOUNCE_TIME 10

#ifdef PFD
gdu_unit pfd;
#endif
#ifdef MFD
gdu_unit mfd;
#endif
#ifdef AP_UNIT
ap_unit ap;
#endif

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting");

#ifdef PFD
  pfd.begin(PFD_CS_PIN, PFD_A_CODE);
  pfd.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("PFD Started");

#endif
#ifdef MFD
  mfd.begin(MFD_CS_PIN, MFD_A_CODE);
  mfd.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("MFD Started");
#endif
#ifdef AP_UNIT
  ap.begin(AP_CS_PIN, MFD_A_CODE);
  ap.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("MFD Started");
#endif

}

void loop() {
#ifdef PFD
  pfd.loop();

  for(int i = 0; i < BUTTON_COUNT; ++i) {
    if (pfd.isPressed(i)) {
      Serial.println(SIMCONNECT_PFD[i]);
    }
  }
#endif
#ifdef MFD
  mfd.loop();

  for(int i = 0; i < BUTTON_COUNT; ++i) {
    if (mfd.isPressed(i)) {
      Serial.println(SIMCONNECT_MFD[i]);
    }
  }
#endif
#ifdef AP_UNIT
  ap.loop();

  for(int i = 0; i < AP_BUTTON_COUNT; ++i) {
    if (ap.isPressed(i)) {
      Serial.println(SIMCONNECT_MFD[i]);
    }
  }
#endif
}