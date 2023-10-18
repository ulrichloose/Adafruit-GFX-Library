#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>

#include "Tandy2K8px7b.h"
#include "Tandy2K16px7b.h"
#include "DSEG7Classic_Bold18px7b.h"

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

char buff0[11] = { 0 };
char buff1[11] = { 0 };

int16_t fg = ST77XX_WHITE;
int16_t bg = ST77XX_BLACK;

Adafruit_ST7735 Lcd = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  Lcd.initR(INITR_144GREENTAB);
  Lcd.setRotation(3);
  Lcd.fillScreen(bg);
  Lcd.setTextColor(fg, bg);
  Lcd.setFont();
  Lcd.setTextSize(1);
  LcdPrint(0, 0, "QWER qwer 012");
  Lcd.setFont(&Tandy2K8px7b);
  LcdPrint(0, 15, "QWER qwer 012");
  LcdPrintBold(0, 24, "QWER qwer 012");
  Lcd.setFont(&Tandy2K16px7b);
  LcdPrint(0, 35, "QWER qwer 012");
  LcdPrintBold(0, 49, "QWER qwer 012");
  Lcd.setFont(&DSEG7Classic_Bold18px7b);
  Lcd.setTextSize(2);
  LcdPrint(0, 120, "23:24");
}

void loop() {
  Lcd.setFont(&DSEG7Classic_Bold18px7b);
  Lcd.setTextColor(fg, bg);
  Lcd.setTextSize(1);

  unsigned long StartTime = millis();

  for (long freq = 0; freq <= 1000; freq++) {
    format(freq, 0, 76);
  }

  format(millis() - StartTime, 0, 76);

  delay(2000);
}
void LcdPrint(int x, int y, const char* tx) {
  Lcd.setCursor(x, y);
  Lcd.print(tx);
}

void LcdPrintBold(int x, int y, const char* tx) {  // simulate Bold Characters by right shifting by one pixel
  Lcd.setCursor(x, y);
  Lcd.print(tx);
  Lcd.setTextColor(fg);
  Lcd.setCursor(x + 1, y);
  Lcd.print(tx);
  Lcd.setTextColor(fg, bg);
}

void format(long f, int x, int y) {
  // 12.345.678
  dtostrf(f, 10, 0, buff0);
  memmove(buff0, buff0 + 2, 2);
  buff0[1] > char(32) ? buff0[2] = '.' : buff0[2] = '!';
  memmove(buff0 + 3, buff0 + 4, 3);
  buff0[5] > char(32) ? buff0[6] = '.' : buff0[6] = '!';

  Lcd.setCursor(x, y);

  for (int i = 0; i < 10; i++) {
    if (buff0[i] == buff1[i]) {  // do not print this digit, add xAdvance to x
      x = Lcd.getCursorX();
      (i == 2 || i == 6) ? Lcd.setCursor(x + 2, y) : Lcd.setCursor(x + 15, y);
    } else {
      Lcd.write(buff0[i]);  // if bg != color delete old digit and print new digit
    }
    buff1[i] = buff0[i];
  }
}
