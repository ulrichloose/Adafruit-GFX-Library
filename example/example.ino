/***************************************************
 * 
 *  
 * tutorial
 * https://learn.adafruit.com/adafruit-1-44-color-tft-with-micro-sd-socket/wiring-and-test
 * GFX Tutorial: https://learn.adafruit.com/adafruit-gfx-graphics-library
 * 
 * Pins
 * LED 3.3 or 5V depending on your display
 * SCK D13
 * SDA D11(MOSI)
 * A0 D8
 * RST D9
 * CS D10
 * GND GND
 * VCC 3.3 or 5V depending on your display
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>
#include "DSEG7Classic_Bold10pt7b.h"

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

char buff0[11] = { ' ' };
char buff1[11] = { ' ' };
char buff2[11] = { ' ' };


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  tft.initR(INITR_144GREENTAB);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  tft.setFont(&DSEG7Classic_Bold10pt7b);
  tft.setTextSize(1);

  // 12.345.678

  unsigned long StartTime = millis();

  for (long freq = 0; freq <= 1000; freq++) {
    format(freq, 0, 80);
  }

  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;

  format(ElapsedTime, 0, 80);

  StartTime = millis();

  for (long freq = 0; freq <= 1000; freq++) {
    format_old(freq, 0, 100);
  }

  CurrentTime = millis();
  ElapsedTime = CurrentTime - StartTime;

  format_old(ElapsedTime, 0, 100);

  delay(5000);
}

void format(long f, int x, int y) {

  dtostrf(f, 10, 0, buff0);
  memmove(buff0, buff0 + 2, 2);
  buff0[1] > char(32) ? buff0[2] = '.' : buff0[2] = '!';
  memmove(buff0 + 3, buff0 + 4, 3);
  buff0[5] > char(32) ? buff0[6] = '.' : buff0[6] = '!';

  tft.setCursor(x, y);

  for (int i = 0; i < 10; i++) {
    if (buff0[i] == buff1[i]) {
      tft.setTextColor(ST77XX_WHITE, ST77XX_WHITE);
      if (i == 2 || i == 6) {
        tft.print('!');
      } else {
        tft.print(' ');
      }
    } else {
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.print(buff0[i]);
    }
    buff1[i] = buff0[i];
  }
}

void format_old(long f, int x, int y) {

  dtostrf(f, 10, 0, buff2);
  memmove(buff2, buff2 + 2, 2);
  buff2[1] > char(32) ? buff2[2] = '.' : buff2[2] = '!';
  memmove(buff2 + 3, buff2 + 4, 3);
  buff2[5] > char(32) ? buff2[6] = '.' : buff2[6] = '!';

  tft.setCursor(x, y);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  for (int i = 0; i < 10; i++) {
    tft.print(buff2[i]);
  }
}