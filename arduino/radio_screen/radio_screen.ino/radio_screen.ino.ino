// https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/examples/graphicstest_st7789/graphicstest_st7789.ino

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>

#include "letters.h"

#if defined(ARDUINO_FEATHER_ESP32)  // Feather Huzzah32
#define TFT_CS 14
#define TFT_RST 15
#define TFT_DC 32

#elif defined(ESP8266)
#define TFT_CS 4
#define TFT_RST 16
#define TFT_DC 5

#else
// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS 10
#define TFT_RST 9  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 8
#endif

#define LEFT_PADDING = 4
#define RIGHT_PADDING = 156

#define LETTER_14_WIDTH = 9
#define LETTER_14_HEIGHT = 18

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

struct CommNavData {
  String name;
  String activ_freq;
  String stby_freq;
  String id;
  String bearing;
  String distance;
  bool selected;
};

CommNavData com1 = { "COM1", "120.750", "119.700", "LFPN TWR", "13", "3", false };
CommNavData com2 = { "COM2", "127.480", "123.450", "LFPN ATIS", "52", "2", true };
CommNavData nav1 = { "NAV1", "114,70", "115.65", "RBT", "150", "21", true };
CommNavData nav2 = { "NAV1", "114,70", "115.65", "RBT", "150", "21", true };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));


  tft.init(170, 320);  // Init ST7789 170x320


  Serial.println(F("Initialized"));


  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void update_nav1_name {
  int x = LEFT_PADDING;
  inf y = 7;

  for char in 

}


