#ifndef RADIO_SCREEN_H
#define RADIO_SCREEN_H

#include <stdint.h>

#define RGB565 uint16_t

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430
#define DARKBLUE 0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE 0X5458
#define LIGHTGREEN 0X841F
#define LGRAY 0XC618
#define LGRAYBLUE 0XA651
#define LBBLUE 0X2B12

#define LEFT_PADDING 4
#define RIGHT_PADDING 156

#define LETTER_14_WIDTH 9
#define LETTER_14_HEIGHT 18
#define LETTER_20_WIDTH 13
#define LETTER_20_HEIGHT 25

class CommNavData
{
private:
    String name;
    String activ_freq;
    String stby_freq;
    String id;
    String bearing;
    String distance;
    bool selected;
    uint16_t display_buffer[160 * 85];
    void setPixel(int x, int y, RGB565 color);
    void drawRectangle(int x, int y, int w, int, h, RGB565 color);
    int min_x, min_y, max_x, max_y;
    bool toBePrinted;

public:
    CommNavData(void);
    void setName(String name);
    void toggleFreq(String freq);
    void setStbdFreq(String freq);
    void setId(String id);
    void setBearing(String bearing);
    void setDistance(String distance);
    void drawBorder(RGB565 color);
    void select(void);
    void unselect(void);
};

class CommData : CommNavData
{
}

class NavData : CommNavData
{
public:
    void setActiveFrequency(String freq);
}

#endif