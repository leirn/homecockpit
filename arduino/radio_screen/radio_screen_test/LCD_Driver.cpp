/*****************************************************************************
* | File        :   LCD_Driver.c
* | Author      :   Waveshare team
* | Function    :   Electronic paper driver
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2022-11-02
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LCD_Driver.h"
#include "ST7789.h"

/*******************************************************************************
function:
  Hardware reset
*******************************************************************************/
static void LCD_Reset(void)
{
    DEV_Digital_Write(DEV_CS_PIN, 0);
    DEV_Delay_ms(20);
    DEV_Digital_Write(DEV_RST_PIN, 0);
    DEV_Delay_ms(20);
    DEV_Digital_Write(DEV_RST_PIN, 1);
    DEV_Delay_ms(20);
}

/*******************************************************************************
function:
  Setting backlight
parameter :
    value : Range 0~255   Duty cycle is value/255
*******************************************************************************/
void LCD_SetBacklight(UWORD Value)
{
    if (Value > 100)
        Value = 100;
    DEV_Set_BL(DEV_BL_PIN, (Value * 2.55));
}

/*******************************************************************************
function:
    Write register address and data
*******************************************************************************/
void LCD_WriteData_Byte(UBYTE da)
{
    DEV_Digital_Write(DEV_CS_PIN, 0);
    DEV_Digital_Write(DEV_DC_PIN, 1);
    DEV_SPI_WRITE(da);
    DEV_Digital_Write(DEV_CS_PIN, 1);
}

void LCD_WriteData_Word(UWORD da)
{
    UBYTE i = (da >> 8) & 0xff;
    DEV_Digital_Write(DEV_CS_PIN, 0);
    DEV_Digital_Write(DEV_DC_PIN, 1);
    DEV_SPI_WRITE(i);
    DEV_SPI_WRITE(da);
    DEV_Digital_Write(DEV_CS_PIN, 1);
}

void LCD_WriteReg(UBYTE da)
{
    DEV_Digital_Write(DEV_CS_PIN, 0);
    DEV_Digital_Write(DEV_DC_PIN, 0);
    DEV_SPI_WRITE(da);
    DEV_Digital_Write(DEV_CS_PIN, 1);
}

/******************************************************************************
function:
    Common register initialization
******************************************************************************/
void LCD_Init(void)
{
    LCD_Reset();

    //************* Start Initial Sequence **********//

    LCD_WriteReg(ST7789_MADCTL); //
    if (HORIZONTAL)
        LCD_WriteData_Byte(0x00);
    else
        LCD_WriteData_Byte(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_ML);

    LCD_WriteReg(ST7789_COLMOD);
    LCD_WriteData_Byte(ST7789_COLDMOD_RGB_65K | ST7789_COLDMOD_COLOR_16BIT_PER_PIX);

    LCD_WriteReg(ST7789_PORCTRL);
    LCD_WriteData_Byte(0x0C);
    LCD_WriteData_Byte(0x0C);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x33);
    LCD_WriteData_Byte(0x33);

    // Add frame rate control ?

    LCD_WriteReg(ST7789_GCTRL);
    LCD_WriteData_Byte(0x35);

    LCD_WriteReg(0xBB);
    LCD_WriteData_Byte(0x13);

    LCD_WriteReg(0xC0);
    LCD_WriteData_Byte(0x2C);

    LCD_WriteReg(0xC2);
    LCD_WriteData_Byte(0x01);

    LCD_WriteReg(0xC3);
    LCD_WriteData_Byte(0x0B);

    LCD_WriteReg(0xC4);
    LCD_WriteData_Byte(0x20);

    LCD_WriteReg(0xC6);
    LCD_WriteData_Byte(0x0F);

    LCD_WriteReg(0xD0);
    LCD_WriteData_Byte(0xA4);
    LCD_WriteData_Byte(0xA1);

    LCD_WriteReg(0xD6);
    LCD_WriteData_Byte(0xA1);

    LCD_WriteReg(0xE0);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x03);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x08);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x15);
    LCD_WriteData_Byte(0x2A);
    LCD_WriteData_Byte(0x44);
    LCD_WriteData_Byte(0x42);
    LCD_WriteData_Byte(0x0A);
    LCD_WriteData_Byte(0x17);
    LCD_WriteData_Byte(0x18);
    LCD_WriteData_Byte(0x25);
    LCD_WriteData_Byte(0x27);

    LCD_WriteReg(0xE1);
    LCD_WriteData_Byte(0x00);
    LCD_WriteData_Byte(0x03);
    LCD_WriteData_Byte(0x08);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x07);
    LCD_WriteData_Byte(0x23);
    LCD_WriteData_Byte(0x2A);
    LCD_WriteData_Byte(0x43);
    LCD_WriteData_Byte(0x42);
    LCD_WriteData_Byte(0x09);
    LCD_WriteData_Byte(0x18);
    LCD_WriteData_Byte(0x17);
    LCD_WriteData_Byte(0x25);
    LCD_WriteData_Byte(0x27);

    LCD_WriteReg(ST7789_INVON);

    LCD_WriteReg(ST7789_SLPOUT);
    delay(120);
    LCD_WriteReg(ST7789_DISPON);
}

/******************************************************************************
function: Set the cursor position
parameter :
    Xstart:   Start UWORD x coordinate
    Ystart:   Start UWORD y coordinate
    Xend  :   End UWORD coordinates
    Yend  :   End UWORD coordinatesen
******************************************************************************/
void LCD_SetCursor(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    if (HORIZONTAL)
    {
        // set the X coordinates
        LCD_WriteReg(ST7789_CASET);
        LCD_WriteData_Byte(Xstart + 35 >> 8);
        LCD_WriteData_Byte(Xstart + 35);
        LCD_WriteData_Byte(Xend + 35 >> 8);
        LCD_WriteData_Byte(Xend + 35);

        // set the Y coordinates
        LCD_WriteReg(ST7789_RASET);
        LCD_WriteData_Byte(Ystart >> 8);
        LCD_WriteData_Byte(Ystart);
        LCD_WriteData_Byte(Yend >> 8);
        LCD_WriteData_Byte(Yend);
    }
    else
    {
        // set the X coordinates
        // TODAO : ST7789_CASET missing ?
        LCD_WriteData_Byte(Ystart >> 8);
        LCD_WriteData_Byte(Ystart);
        LCD_WriteData_Byte(Yend >> 8);
        LCD_WriteData_Byte(Yend);
        // set the Y coordinates
        LCD_WriteReg(ST7789_RASET);
        LCD_WriteData_Byte(Xstart + 35 >> 8);
        LCD_WriteData_Byte(Xstart + 35);
        LCD_WriteData_Byte(Xend + 35 >> 8);
        LCD_WriteData_Byte(Xend + 35);
    }

    LCD_WriteReg(ST7789_RAMWR);
}

/******************************************************************************
function: Clear screen function, refresh the screen to a certain color
parameter :
    Color :   The color you want to clear all the screen
******************************************************************************/
void LCD_Clear(UWORD Color)
{
    UWORD i, j;
    LCD_SetCursor(0, 0, LCD_WIDTH, LCD_HEIGHT);
    for (i = 0; i < LCD_WIDTH; i++)
    {
        for (j = 0; j < LCD_HEIGHT; j++)
        {
            LCD_WriteData_Word(Color);
        }
    }
}

/******************************************************************************
function: Refresh a certain area to the same color
parameter :
    Xstart:   Start UWORD x coordinate
    Ystart:   Start UWORD y coordinate
    Xend  :   End UWORD coordinates
    Yend  :   End UWORD coordinates
    color :   Set the color
******************************************************************************/
void LCD_ClearWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD color)
{
    UWORD i, j;
    LCD_SetCursor(Xstart, Ystart, Xend, Yend);
    for (i = Ystart; i < Yend; i++)
    {
        for (j = Xstart; j < Xend; j++)
        {
            LCD_WriteData_Word(color);
        }
    }
}

/******************************************************************************
function: Set the color of an area
parameter :
    Xstart:   Start UWORD x coordinate
    Ystart:   Start UWORD y coordinate
    Xend  :   End UWORD coordinates
    Yend  :   End UWORD coordinates
    Color :   Set the color
******************************************************************************/
void LCD_SetWindowColor(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color)
{
    LCD_SetCursor(Xstart, Ystart, Xend, Yend);
    LCD_WriteData_Word(Color);
}

/******************************************************************************
function: Draw a UWORD
parameter :
    X     :   Set the X coordinate
    Y     :   Set the Y coordinate
    Color :   Set the color
******************************************************************************/
void LCD_SetUWORD(UWORD x, UWORD y, UWORD Color)
{
    LCD_SetCursor(x, y, x, y);
    LCD_WriteData_Word(Color);
}
