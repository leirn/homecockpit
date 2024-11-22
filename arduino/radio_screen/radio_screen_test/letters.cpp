#include "letters.h"

const void *get_20_letter(char letter) {
  switch (letter) {
    case 'A':
      return &CHAR_20_A;
    case 'B':
      return &CHAR_20_B;
    case 'C':
      return &CHAR_20_C;
    case 'D':
      return &CHAR_20_D;
    case 'E':
      return &CHAR_20_E;
    case 'F':
      return &CHAR_20_F;
    case 'G':
      return &CHAR_20_G;
    case 'H':
      return &CHAR_20_H;
    case 'I':
      return &CHAR_20_I;
    case 'J':
      return &CHAR_20_J;
    case 'K':
      return &CHAR_20_K;
    case 'L':
      return &CHAR_20_L;
    case 'M':
      return &CHAR_20_M;
    case 'N':
      return &CHAR_20_N;
    case 'O':
      return &CHAR_20_O;
    case 'P':
      return &CHAR_20_P;
    case 'Q':
      return &CHAR_20_Q;
    case 'R':
      return &CHAR_20_R;
    case 'S':
      return &CHAR_20_S;
    case 'T':
      return &CHAR_20_T;
    case 'U':
      return &CHAR_20_U;
    case 'V':
      return &CHAR_20_V;
    case 'W':
      return &CHAR_20_W;
    case 'X':
      return &CHAR_20_X;
    case 'Y':
      return &CHAR_20_Y;
    case 'Z':
      return &CHAR_20_Z;
    case '0':
      return &CHAR_20_0;
    case '1':
      return &CHAR_20_1;
    case '2':
      return &CHAR_20_2;
    case '3':
      return &CHAR_20_3;
    case '4':
      return &CHAR_20_4;
    case '5':
      return &CHAR_20_5;
    case '6':
      return &CHAR_20_6;
    case '7':
      return &CHAR_20_7;
    case '8':
      return &CHAR_20_8;
    case '9':
      return &CHAR_20_9;
    case '.':
      return &CHAR_20_DOT;
    case '°':
      return &CHAR_20_DEGREE;
    default:
      return &CHAR_20_DOT;
  }
}

const void *get_14_letter(char letter) {
  switch (letter) {
    case 'A':
      return &CHAR_14_A;
    case 'B':
      return &CHAR_14_B;
    case 'C':
      return &CHAR_14_C;
    case 'D':
      return &CHAR_14_D;
    case 'E':
      return &CHAR_14_E;
    case 'F':
      return &CHAR_14_F;
    case 'G':
      return &CHAR_14_G;
    case 'H':
      return &CHAR_14_H;
    case 'I':
      return &CHAR_14_I;
    case 'J':
      return &CHAR_14_J;
    case 'K':
      return &CHAR_14_K;
    case 'L':
      return &CHAR_14_L;
    case 'M':
      return &CHAR_14_M;
    case 'N':
      return &CHAR_14_N;
    case 'O':
      return &CHAR_14_O;
    case 'P':
      return &CHAR_14_P;
    case 'Q':
      return &CHAR_14_Q;
    case 'R':
      return &CHAR_14_R;
    case 'S':
      return &CHAR_14_S;
    case 'T':
      return &CHAR_14_T;
    case 'U':
      return &CHAR_14_U;
    case 'V':
      return &CHAR_14_V;
    case 'W':
      return &CHAR_14_W;
    case 'X':
      return &CHAR_14_X;
    case 'Y':
      return &CHAR_14_Y;
    case 'Z':
      return &CHAR_14_Z;
    case '0':
      return &CHAR_14_0;
    case '1':
      return &CHAR_14_1;
    case '2':
      return &CHAR_14_2;
    case '3':
      return &CHAR_14_3;
    case '4':
      return &CHAR_14_4;
    case '5':
      return &CHAR_14_5;
    case '6':
      return &CHAR_14_6;
    case '7':
      return &CHAR_14_7;
    case '8':
      return &CHAR_14_8;
    case '9':
      return &CHAR_14_9;
    case '.':
      return &CHAR_14_DOT;
    case '°':
      return &CHAR_14_DEGREE;
    default:
      return &CHAR_20_DOT;
  }
}

// compute RGB565 color from 16-bit color and pixel transparency
uint16_t compute_color(uint16_t color, uint8_t pixel_transparency) {
  uint16_t r = (color & 0xF800) >> 11;
  uint16_t g = (color & 0x07E0) >> 5;
  uint16_t b = (color & 0x001F);
  r = (r * pixel_transparency) >> 8;
  g = (g * pixel_transparency) >> 8;
  b = (b * pixel_transparency) >> 8;
  return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | ((b & 0x1F));
}
