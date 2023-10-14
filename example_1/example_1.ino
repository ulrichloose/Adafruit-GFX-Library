#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>

#include "Tandy2K8px7b.h"
#include "Tandy2K16px7b.h"
#include "DSEG7Classic_Bold18px7b.h"
#include "DSEG7Classic_Bold36px7b.h"

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

char buff0[11] = { 0 };
char buff1[11] = { 0 };

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  tft.initR(INITR_144GREENTAB);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE, ST7735_BLUE);
  tft.setFont();
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.print("QWER qwer 012");
  tft.setFont(&Tandy2K8px7b);
  tft.setCursor(0, 15);
  tft.print("QWER qwer 012");
  tft.setCursor(0, 24);
  tft.print("QWER qwer 012");
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(1, 24);
  tft.print("QWER qwer 012");
  tft.setFont(&Tandy2K16px7b);
  tft.setTextColor(ST77XX_WHITE, ST7735_BLUE);
  tft.setCursor(0, 35);
  tft.print("QWER qwer 012");
  tft.setCursor(0, 49);
  tft.print("QWER qwer 012");
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(1, 49);
  tft.print("QWER qwer 012");

  tft.setTextColor(ST77XX_WHITE, ST7735_BLUE);
  tft.setFont(&DSEG7Classic_Bold18px7b);
  tft.setTextSize(2);
  tft.setCursor(0, 120);
  tft.print("23:24");
}

void loop() {
  tft.setTextColor(ST77XX_WHITE, ST7735_BLUE);
  tft.setFont(&DSEG7Classic_Bold18px7b);
  tft.setTextSize(1);

  unsigned long StartTime = millis();

  for (long freq = 0; freq <= 1000; freq++) {
    format(freq, 0, 76);
  }

  format(millis() - StartTime, 0, 76);

  delay(2000);

/*
  for (long freq = 0; freq < 12345678; freq = freq + 111) {
    format(freq, 0, 76);
  }
*/

}

void format(long f, int x, int y) {
  // 12.345.678
  dtostrf(f, 10, 0, buff0);
  memmove(buff0, buff0 + 2, 2);

  buff0[1] > char(32) ? buff0[2] = '.' : buff0[2] = '!';
  memmove(buff0 + 3, buff0 + 4, 3);
  buff0[5] > char(32) ? buff0[6] = '.' : buff0[6] = '!';

  tft.setCursor(x, y);
  //tft.print(buff0);

  for (int i = 0; i < 10; i++) {
    if (buff0[i] == buff1[i]) {  // do not print this digit, add xAdvance to x
      x = tft.getCursorX();
      if (i == 2 || i == 6) {
        tft.setCursor(x + 2, y);  // width of . or small space
      } else {
        tft.setCursor(x + 15, y);  // width of all other digits
      }
    } else {
      tft.write(buff0[i]);  // if bg != color delete old digit and print new digit
    }
    buff1[i] = buff0[i];
  }
}
