#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"

#include "letters.h"
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

#define LIGHT_GREY ((23 << 11) | (47 << 5) | 23)

#define FRAME_RADIUS 5

CommNavData com1 = {"COM1", "123.505", "131.501", "LFPN TWR", "182", "20", false};
CommNavData com2 = {"COM2", "120.750", "128.480", "LFPN ATIS", "150", "24", true};
CommNavData nav1 = {"NAV1", "114.70", "115.65", "RBT", "127", "10", false};
CommNavData nav2 = {"NAV2", "110.54", "116.52", "EPR", "321", "6.2", true};

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Start configuration");

  Config_Init();
  LCD_Init();

  LCD_SetBacklight(100);

  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, ROTATE_90, WHITE);
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(5000);

  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, ROTATE_90, WHITE);
  Paint_Clear(BLACK);
  init_display();
  Serial.println("Loop");
}

void init_display()
{
  display_nav1_border();
  display_nav2_border();
  display_com1_border();
  display_com2_border();
  update_nav1_name();
  // update_nav2_name();
  // update_com1_name();
  // update_com2_name();
}

CommNavData com1 = {"COM1", "123.505", "131.501", "LFPN TWR", "182", "20", false};
CommNavData com2 = {"COM2", "120.750", "128.480", "LFPN ATIS", "150", "24", true};
CommNavData nav1 = {"NAV1", "114.70", "115.65", "RBT", "127", "10", false};
CommNavData nav2 = {"NAV2", "110.54", "116.52", "EPR", "321", "6.2", true};

void setNav1ActiveFreq(String freq)
{
  int i = 0;
  for (i = 0; i < freq.length(); ++i)
  {
    if (i < nav1.activ_freq.length())
    {
      if (freq.charAt(i) != nav1.activ_freq.charAt(i))
      {
        const uint8_t **var = (const uint8_t **)get_20_letter(freq.charAt(i));
        display_letter(RIGHT_PADDING - (7 - i) * LETTER_20_WIDTH, 60, var, LETTER_20_WIDTH, LETTER_20_HEIGHT, GREEN);
      }
    }
    else
    {
      const uint8_t **var = (const uint8_t **)get_20_letter(freq.charAt(i));
      display_letter(RIGHT_PADDING - (7 - i) * LETTER_20_WIDTH, 60, var, LETTER_20_WIDTH, LETTER_20_HEIGHT, GREEN);
    }
  }
  for (i; i < 7; ++i)
  {
    remove_letter(RIGHT_PADDING - (7 - i) * LETTER_20_WIDTH, 60, LETTER_20_WIDTH, LETTER_20_HEIGHT);
  }
}

void display_nav1_border()
{
  display_border(0, 0, nav1.selected);
}

void display_nav2_border()
{
  display_border(0, HALF_HEIGHT, nav2.selected);
}

void display_com1_border()
{
  display_border(HALF_WIDTH, 0, com1.selected);
}

void display_com2_border()
{
  display_border(HALF_WIDTH, HALF_HEIGHT, com2.selected);
}

void display_border(int x, int y, bool selected)
{
  int color = LIGHT_GREY;
  if (selected)
  {
    color = GREEN;
  }
  // Paint_DrawRoundRectangle(x + 1, y + 1, x + 158, x + 83, color, DOT_PIXEL_2X2, DRAW_FILL_EMPTY, FRAME_RADIUS);
  Paint_DrawRectangle(x + 1, y + 1, x + 158, y + 83, color, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
}

void update_nav1_name()
{
  update_comm_name(nav1.name, LEFT_PADDING, 7);
}

void update_nav2_name()
{
  update_comm_name(nav2.name, LEFT_PADDING, HALF_HEIGHT + 7);
}

void update_com1_name()
{
  update_comm_name(com1.name, SCREEN_WIDTH - (LETTER_14_WIDTH * com1.name.length()), 7);
}

void update_com2_name()
{
  update_comm_name(com2.name, SCREEN_WIDTH - (LETTER_14_WIDTH * com2.name.length()), HALF_HEIGHT + 7);
}

void update_comm_name(String name, int x, int y)
{
  for (auto c : name)
  {
    const uint8_t **var = (const uint8_t **)get_14_letter(c);
    Serial.println("Try to print letter")
        display_letter(x, y, var, LETTER_14_WIDTH, LETTER_14_HEIGHT, MAGENTA);
  }
}

void display_letter(int x, int y, const uint8_t **bitmap, int bitmap_width, int bitmap_height, uint16_t color)
{
  for (int w = 0; w < bitmap_width; w++)
  {
    for (int h = 0; h < bitmap_width; h++)
    {
      uint16_t blended_color = compute_color(bitmap[h][w], color);
      Paint_SetPixel(x + w, y + h, blended_color);
    }
  }
}

void remove_letter(int x, int y, int h, int w)
{
  Paint_DrawRectangle(x, y, w, h, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
}
