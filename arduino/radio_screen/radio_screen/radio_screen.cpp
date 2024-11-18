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

void CommNavData::drawBorder(uint16_t color)
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

void CommNavData::setPixel(int x, int y, uint16_t color)
{
    this->display_buffer[y << 8 + x] = color;
    min_x = min(min_x, x);
    min_y = min(min_y, y);
    max_x = max(max_x, x);
    max_y = max(max_y, y);
    toBePrinted = true;
}