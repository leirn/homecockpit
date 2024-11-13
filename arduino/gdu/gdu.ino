#include "gdu_unit.h"
#include "pmfd_unit.h"
#include "ap_unit.h"
#include "comm_nav_unit.h"

#define PFD 1
#define MFD 1
#define AP_UNIT 1
#define PMFD_UNIT 1
#define COMM_NAV_UNIT 1

#define PFD_CS_PIN 53
#define MFD_CS_PIN 53
#define AP_CS_PIN 53
#define PMFD_CS_PIN 53
#define COMM_NAV_CS_PIN 53

#define PFD_A_CODE 0         // 1 SPI address
#define MFD_A_CODE 1         // 1 SPI address
#define AP_A_CODE 0b100      // 4 SPI addresses
#define PMFD_A_CODE 1        // 2 SPI address
#define COMM_NAV_A_CODE 0b10 // 1 SPI address

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
#ifdef PMFD_UNIT
pmfd_unit pmfd;
#endif
#ifdef COMM_NAV_UNIT
comm_nav_unit comm_nav;
#endif

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("[DEBUG] Starting");

#ifdef PFD
  pfd.begin(PFD_CS_PIN, PFD_A_CODE);
  pfd.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("[DEBUG] PFD Started");

#endif
#ifdef MFD
  mfd.begin(MFD_CS_PIN, MFD_A_CODE);
  mfd.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("[DEBUG] MFD Started");
#endif
#ifdef AP_UNIT
  ap.begin(AP_CS_PIN, MFD_A_CODE);
  ap.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("[DEBUG] Auto-pilot Started");
#endif
#ifdef PMFD_UNIT
  pmfd.begin(PMFD_CS_PIN, PMFD_A_CODE);
  pmfd.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("[DEBUG] MFD Started");
#endif
#ifdef COMM_NAV_UNIT
  comm_nav.begin(COMM_NAV_CS_PIN, COMM_NAV_A_CODE);
  comm_nav.setDebounceTime(DEBOUNCE_TIME);

  Serial.println("[DEBUG] MFD Started");
#endif

  Serial.setTimeout(100); // Avoid to wait to long for inputs
}

void loop()
{

  String receivedString = Serial.readStringUntil("\n");
  parseReceivedString(receivedString);

#ifdef PFD
  pfd.loop();

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    if (pfd.isPressed(i))
    {
      Serial.println(pfd.getSimconnectEvent(PFD, i));
    }
  }
#endif
#ifdef MFD
  mfd.loop();

  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    if (mfd.isPressed(i))
    {
      Serial.println(mfd.getSimconnectEvent(MFD, i));
    }
  }
#endif
#ifdef AP_UNIT
  ap.loop();

  for (int i = 0; i < AP_BUTTON_COUNT; ++i)
  {
    if (ap.isPressed(i))
    {
      Serial.println(ap.getSimconnectEvent(i));
    }
  }
#endif
#ifdef PMFD_UNIT
  pmfd.loop();

  for (int i = 0; i < PMFD_BUTTON_COUNT; ++i)
  {
    if (pmfd.isPressed(i))
    {
      Serial.println(pmfd.getSimconnectEvent(i));
    }
  }
#endif
#ifdef COMM_NAV_UNIT
  pmfd.loop();

  for (int i = 0; i < COMM_NAV_BUTTON_COUNT; ++i)
  {
    if (comm_nav.isPressed(i))
    {
      Serial.println(comm_nav.getSimconnectEvent(i));
    }
  }
#endif
}

void parseReceivedString(String received)
{
  // https://docs.flightsimulator.com/html/Programming_Tools/SimVars/Aircraft_SimVars/Aircraft_RadioNavigation_Variables.htm#COM1%20STORED%20FREQUENCY
  // COMM part
  if (received.startsWith("COM ACTIVE BEARING:"))
  {
    // set COMx bearing
  }
  else if (received.startsWith("COM ACTIVE DISTANCE:"))
  {
    // set COMx distance
  }
  else if (received.startsWith("COM ACTIVE FREQUENCY:"))
  {
    // set COMx active freq
  }
  else if (received.startsWith("COM STANDBY FREQUENCY:"))
  {
    // set COMx standby freq
  }
  else if (received.startsWith("COM ACTIVE FREQ IDENT:"))
  {
    // set COMx active freq identity
  }
  else if (received.startsWith("COM ACTIVE FREQ TYPE:"))
  {
    // set COMx active freq type
  }
  else if (received.startsWith("COM STATUS:"))
  {
    // wether the com exists and works
  }

  // NAV part
  else if (received.startsWith("NAV RADIAL"))
  {
    // set NAV radial
  }
  else if (received.startsWith("NAV VOR DISTANCE"))
  {
    // set NAV distance
  }
  else if (received.startsWith("NAV ACTIVE FREQUENCY:"))
  {
    // set NAVx active freq
  }
  else if (received.startsWith("NAV STANDBY FREQUENCY:"))
  {
    // set NAVx standby freq
  }
  else if (received.startsWith("NAV IDENT"))
  {
    // set NAV active freq identity
  }
  else if (received.startsWith("NAV AVAILABLE"))
  {
    // wether the nav exists
  }
}