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

#define LEFT_PADDING 4
#define RIGHT_PADDING 156

#define LETTER_14_WIDTH 9
#define LETTER_14_HEIGHT 18
#define LETTER_20_WIDTH 13
#define LETTER_20_HEIGHT 25

#define HALF_HEIGHT 85
#define HALF_WIDTH 160
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 170

#define LIGHT_GREY ((23 << 11) |  (47 << 5) | 23)

#define FRAME_RADIUS 5

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

CommNavData com1 = { "COM1", "", "", "", "", "", false };
CommNavData com2 = { "COM2", "", "", "", "", "", true };
CommNavData nav1 = { "NAV1", "", "", "", "", "", true };
CommNavData nav2 = { "NAV1", "", "", "", "", "", true };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));


  tft.init(170, 320);  // Init ST7789 170x320
  tft.setRotation(1); // Set screen in landscape mode


  Serial.println(F("Initialized"));


  tft.fillScreen(ST77XX_BLACK); // initialize screen with black background

  init_display(); // Compute the display
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
}

void init_display() {
  display_nav1_border();
  display_nav2_border();
  display_com1_border();
  display_com2_border();
  update_nav1_name();
  update_nav2_name();
  update_com1_name();
  update_com2_name();
}


void setNav1ActiveFreq(String freq) {
  int i = 0;
  for(i = 0; i < freq.length(); ++i) {
    if (i < nav1.activ_freq.length()) {
      if (freq.charAt(i) != nav1.activ_freq.charAt(i)) {
        const uint8_t **var = (const uint8_t **)get_20_letter(freq.charAt(i));
        display_letter(RIGHT_PADDING - (7- i) *  LETTER_20_WIDTH, 60, var, LETTER_20_WIDTH, LETTER_20_HEIGHT, ST77XX_GREEN);
      }
    } 
    else {
      const uint8_t **var = (const uint8_t **)get_20_letter(freq.charAt(i));
      display_letter(RIGHT_PADDING - (7- i) *  LETTER_20_WIDTH, 60, var, LETTER_20_WIDTH, LETTER_20_HEIGHT, ST77XX_GREEN);
    }
  }
  for(i; i< 7; ++i) {
    remove_letter(RIGHT_PADDING - (7- i) *  LETTER_20_WIDTH, 60,LETTER_20_WIDTH, LETTER_20_HEIGHT);
  }
}

void display_nav1_border() {
  display_border(0, 0, nav1.selected);
}

void display_nav2_border() {
  display_border(0, HALF_HEIGHT, nav2.selected);
}

void display_com1_border() {
  display_border(HALF_WIDTH, 0, com1.selected);
}

void display_com2_border() {
  display_border(HALF_WIDTH, HALF_HEIGHT, com2.selected);
}

void display_border(int x, int y, bool selected) {
  int color = LIGHT_GREY;
  if (selected) {
    color = ST77XX_GREEN;
  }
  tft.drawRoundRect(x + 1, y + 1, x + 158, x + 83, FRAME_RADIUS, color);
}

void update_nav1_name(){
  update_comm_name(nav1.name, LEFT_PADDING, 7);
}

void update_nav2_name(){
  update_comm_name(nav2.name, LEFT_PADDING, HALF_HEIGHT + 7);
}

void update_com1_name(){
  update_comm_name(com1.name, SCREEN_WIDTH - (LETTER_14_WIDTH * com1.name.length()), 7);
}

void update_com2_name(){
  update_comm_name(com2.name,  SCREEN_WIDTH - (LETTER_14_WIDTH * com2.name.length()), HALF_HEIGHT + 7);
}

void update_comm_name(String name, int x, int y) {
  for(auto c : name)
    {
      const uint8_t **var = (const uint8_t **)get_14_letter(c);
      display_letter(x, y, var, LETTER_14_WIDTH, LETTER_14_HEIGHT, ST77XX_MAGENTA);
    }

}

void display_letter(int x, int y, const uint8_t ** bitmap, int bitmap_width, int bitmap_height, uint16_t color) {
  for(int w = 0; w < bitmap_width; w++) {
    for(int h = 0; h < bitmap_width; h++) {
      uint16_t blended_color = compute_color(bitmap[h][w], color);
      tft.writePixel(x + w, y + h, blended_color);
    }
  }
}

void remove_letter(int x, int y, int h, int w) {
  tft.fillRect(x, y, w, h, ST77XX_BLACK);
}


