#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"

#include "letters.h"

#define DEBUG

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 170

#define COM1_X 160
#define COM1_Y 0

#define COM2_X 160
#define COM2_Y 85

#define NAV1_X 0
#define NAV1_Y 0

#define NAV2_X 0
#define NAV2_Y 85

#define LIGHT_GREY ((23 << 11) | (47 << 5) | 23)

#define FRAME_RADIUS 5

CommData com1;
CommData com2;
NavData nav1;
NavData nav2;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Start configuration");

  Config_Init();
  LCD_Init();

  LCD_SetBacklight(100);

  com1.setOffsetX(COM1_X);
  com1.setOffsetY(COM1_Y);
  com1.setName("COM1");
  com1.select();
  com2.setOffsetX(COM2_X);
  com2.setOffsetY(COM2_Y);
  com2.setName("COM2");
  nav1.setOffsetX(NAV1_X);
  nav1.setOffsetY(NAV1_Y);
  nav1.setName("NAV1");
  nav1.select();
  nav2.setOffsetX(NAV2_X);
  nav2.setOffsetY(NAV2_Y);
  nav2.setName("NAV2");

#ifdef DEBUG
  com1.setActiveFrequency("123.505");
  com2.setActiveFrequency("123.505");
  nav1.setActiveFrequency("114.70");
  nav2.setActiveFrequency("114.70");

  com1.setStbyFrequency("123.505");
  com2.setStbyFrequency("123.505");
  nav1.setStbyFrequency("114.70");
  nav2.setStbyFrequency("114.70");

  com1.setId("LFPN");
  com2.setId("LFMD");
  nav1.setId("RBT");
  nav2.setId("RBT");

  com1.setDistance("25");
  com2.setDistance("12");
  nav1.setDistance("25");
  nav2.setDistance("15");

  com1.setBearing("025");
  com2.setBearing("120");
  nav1.setBearing("253");
  nav2.setBearing("152");
#endif

  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, ROTATE_90, WHITE);
  refresh_display();
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(5000);

  refresh_display();
  Serial.println("Loop");
}

void init_display()
{
  refresh_display();
}

void refresh_display()
{
  com1.refresh();
  com2.refresh();
  nav1.refresh();
  nav2.refresh();
}