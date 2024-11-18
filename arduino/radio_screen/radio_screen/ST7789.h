#ifndef ST7789_H
#define ST7789_H

// List of ST7789 commands

#define ST7789_NOP 0x00       // No Operation
#define ST7789_SWRESET 0x01   // Software Reset
#define ST7789_RDDID 0x04     // Read Display ID
#define ST7789_RDDST 0x09     // Read Display Status
#define ST7789_RDDPM 0x0a     // Read Display Power Mode
#define ST7789_RDDMADCTL 0x0b // Read Display MADCTL
#define ST7789_RDDCOLMOD 0x0c // Read Display Pixel Format
#define ST7789_RDDIM 0x0d     // Read Display Image Mode
#define ST7789_RDDSM 0x0e     // Read Display Signal Mode
#define ST7789_RDDSDR 0x0f    // Read Display Self-Diagnostic Result (ST7789V)

#define ST7789_SLPIN 0x10  // Sleep In
#define ST7789_SLPOUT 0x11 // Sleep Out
#define ST7789_PTLON 0x12  // Partial Display Mode On
#define ST7789_NORON 0x13  // Normal Display Mode On

#define ST7789_INVOFF 0x20  // Display Inversion Off
#define ST7789_INVON 0x21   // Display Inversion On
#define ST7789_GAMSET 0x26  // Gamma Set
#define ST7789_DISPOFF 0x28 // Display Off
#define ST7789_DISPON 0x29  // Display On
#define ST7789_CASET 0x2a   // Column Address Set
#define ST7789_RASET 0x2b   // Row Address Set
#define ST7789_RAMWR 0x2c   // Memory Write
#define ST7789_RAMRD 0x2e   // Memory Read

#define ST7789_PTLAR 0x30    // Partial Area
#define ST7789_VSCRDEF 0x33  // Vertical Scrolling Definition
#define ST7789_TEOFF 0x34    // Tearing Effect Line Off
#define ST7789_TEON 0x35     // Tearing Effect Line On
#define ST7789_MADCTL 0x36   // Memory Data Access Control
#define ST7789_VSCRSADD 0x37 // Vertical Scrolling Start Address of RAM
#define ST7789_IDMOFF 0x38   // Idle Mode Off
#define ST7789_IDMON 0x39    // Idle Mode On
#define ST7789_COLMOD 0x3a   // Interface Pixel Format
#define ST7789_RAMWRC 0x3c   // Memory Write Continue
#define ST7789_RAMRDC 0x3e   // Memory Read Continue
#define ST7789_TESCAN 0x44   // Set Tear Scanline
#define ST7789_RDTESCAN 0x45 // Read Tear Scanline

#define ST7789_WRDISBV 0x51  // Write Display Brightness
#define ST7789_RDDISBV 0x52  // Read Display Brightness Value
#define ST7789_WRCTRLD 0x53  // Write CTRL Display
#define ST7789_RDCTRLD 0x54  // Read CTRL Display
#define ST7789_WRCACE 0x55   // Write Content Adaptive Brightness Control and Color Enhancement
#define ST7789_RDCABC 0x56   // Read Content Adaptive Brightness Control
#define ST7789_WRCABCMB 0x5e // Write CABC Minimum Brightness
#define ST7789_RDCABCMB 0x5f // Read CABC Minimum Brightness
#define ST7789_RDCABCMB 0x68 // Read Automatic Brightness Control Self-Diagnostic Result

#define ST7789_RDID1 0xda // Read ID1
#define ST7789_RDID1 0xdb // Read ID2
#define ST7789_RDID1 0xdc // Read ID3

#define ST7789_MADCTL_MY 0x80
#define ST7789_MADCTL_MX 0x40
#define ST7789_MADCTL_MV 0x20
#define ST7789_MADCTL_ML 0x10
#define ST7789_MADCTL_BGR 0x08
#define ST7789_MADCTL_MH 0x04
#define ST7789_MADCTL_RGB 0x00

#endif