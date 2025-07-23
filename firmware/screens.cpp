#include "screens.h"
#include <U8g2lib.h>

void drawLocoScreen(U8G2& u8g2, int speedLoco1, int speedLoco2) {
  static const unsigned char image_arrow_right_1_bits[] = {0x10,0x20,0x7f,0x20,0x10};
  static const unsigned char image_arrow_right_copy_bits[] = {0x04,0x02,0x7f,0x02,0x04};
  static const unsigned char image_Ok_btn_bits[] = {0x3e,0x63,0x51,0x49,0x41,0x63,0x3e};

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.drawLine(63, 0, 63, 53);

  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(69, 11, "br187  -  3");

  u8g2.drawStr(4, 11, "br285  -  2");

  u8g2.setFont(u8g2_font_6x12_tr);

  char speedLoco1Str[10];
  sprintf(speedLoco1Str, "%dkm/h", speedLoco1);
  u8g2.drawStr(17, 35, speedLoco1Str);

  char speedLoco2Str[10];
  sprintf(speedLoco2Str, "%dkm/h", speedLoco2);
  u8g2.drawStr(82, 35, speedLoco2Str);

  u8g2.drawXBM(4, 28, 7, 7, image_Ok_btn_bits);
  u8g2.drawXBM(69, 28, 7, 7, image_Ok_btn_bits);

  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(2, 62, "Next");

  u8g2.drawStr(94, 62, "Next");

  u8g2.drawStr(55, 62, "Menu");

  u8g2.drawXBM(38, 6, 7, 5, image_arrow_right_copy_bits);

  u8g2.drawXBM(103, 6, 7, 5, image_arrow_right_1_bits);
  u8g2.sendBuffer();
}