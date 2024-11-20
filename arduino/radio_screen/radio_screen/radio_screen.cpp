#include "radio_screen.h"

CommNavData::CommNavData(void)
{
    this->name = "";
    this->activ_freq = "";
    this->stby_freq = "";
    this->id = "";
    this->bearing = "";
    this->distance = "";
    this->selected = false;
    this->display_buffer = {0};
}

void CommNavData::setName(String name)
{
    this->name = name;
}

void CommNavData::toggleFreq(String freq)
{
    if (this->activ_freq == freq)
    {
        this->activ_freq = this->stby_freq;
    }
    else
    {
        this->stby_freq = this->activ_freq;
        this->activ_freq = freq;
    }
}

void CommNavData::setStbdFreq(String freq)
{
    this->stby_freq = freq;
}

void CommNavData::setId(String id)
{
    this->id = id;
}

void CommNavData::setBearing(String bearing)
{
    this->bearing = bearing;
}

void CommNavData::setDistance(String distance)
{
    this->distance = distance;
}

void CommNavData::select(void)
{
    this->selected = true;
}

void CommNavData::unselect(void)
{
    this->selected = false;
}

void CommNavData::drawBorder(RGB565 color)
{
    int color = LGRAY;
    if (this->selected)
    {
        color = GREEN;
    }

    for (int x = 1; x < 159; ++x)
    {
        this->setPixel(x, 1, color);
        this->setPixel(x, 2, color);
        this->setPixel(x, 83, color);
        this->setPixel(x, 84, color);
    }

    for (int y = 1; y < 84; ++y)
    {
        this->setPixel(1, y, color);
        this->setPixel(2, y, color);
        this->setPixel(157, y, color);
        this->setPixel(158, y, color);
    }
}

void CommNavData::drawRectangle(int x, int y, int w, int h, RGB565 color)
{
    min_x = min(min_x, x);
    min_y = min(min_y, y);
    max_x = max(max_x, x + w);
    max_y = max(max_y, y + h);
    toBePrinted = true;
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            this->display_buffer[(y + j) << 8 + (x + i)] = color;
        }
    }
}

void CommNavData::setPixel(int x, int y, RGB565 color)
{
    this->display_buffer[y << 8 + x] = color;
    min_x = min(min_x, x);
    min_y = min(min_y, y);
    max_x = max(max_x, x);
    max_y = max(max_y, y);
    toBePrinted = true;
}

void CommNavData::displayLetter(int x, int y, const uint8_t **bitmap, int bitmap_width, int bitmap_height, uint16_t color)
{
    for (int w = 0; w < bitmap_width; w++)
    {
        for (int h = 0; h < bitmap_width; h++)
        {
            uint16_t blended_color = compute_color(bitmap[h][w], color);
            this->setPixel(x + w, y + h, blended_color);
        }
    }
}

void CommNavData::removeLetter(int x, int y, int h, int w)
{
    this->drawRectangle(x, y, w, h, BLACK);
}

void NavData::setActiveFrequency(String freq)
{
    int i = 0;
    for (i = 0; i < freq.length(); ++i)
    {
        if (i < this->activ_freq.length())
        {
            if (freq.charAt(i) != this->activ_freq.charAt(i))
            {
                const uint8_t **var = (const uint8_t **)get_20_letter(freq.charAt(i));
                this->display_letter(RIGHT_PADDING - (7 - i) * LETTER_20_WIDTH, 60, var, LETTER_20_WIDTH, LETTER_20_HEIGHT, GREEN);
            }
        }
        else
        {
            const uint8_t **var = (const uint8_t **)get_20_letter(freq.charAt(i));
            this->(RIGHT_PADDING - (7 - i) * LETTER_20_WIDTH, 60, var, LETTER_20_WIDTH, LETTER_20_HEIGHT, GREEN);
        }
    }
    for (i; i < 7; ++i)
    {
        this->(RIGHT_PADDING - (7 - i) * LETTER_20_WIDTH, 60, LETTER_20_WIDTH, LETTER_20_HEIGHT);
    }
    this->activ_freq = freq;
}