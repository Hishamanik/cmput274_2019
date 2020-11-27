/*
  LCD image drawing test.

  Draws an image to the screen.  The image is stored in "parrot.lcd" on
  the SD card.  The image file contains only raw pixel byte-pairs.
*/


#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include "lcd_image.h"

MCUFRIEND_kbv tft;

// Pin for SD Card
#define SD_CS 10

// must specify the dimensions of the parrot, nothing in the .lcd file
// format contains this, so you have to enter it yourself
// NOTE: the parrot.lcd file is only a square patch of the original .bmp
//lcd_image_t test_image = { "yeg-big.lcd", 128, 128 };
// lcd_image_t test_image = { "yeg-sm.lcd", 128, 128 };
 lcd_image_t test_image = { "yeg-big.lcd", 2048, 2048 };

/**
 * Initializes the SD card in order to read the parrot lcd image
 */
void initSDCard() {
    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
        Serial.println("failed! Is it inserted properly?");
        while (true) {}
    }
    Serial.println("OK!");
}

void setup() {
    init();

    Serial.begin(9600);

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    initSDCard();

    // clear to yellow
    tft.fillScreen(tft.color565(0xff, 0xff, 0x00));
}

int main() {
    setup();

    Serial.println("Drawing parrot");

    lcd_image_draw(&test_image, &tft, 0, 0, 0, 0, tft.width(), tft.height());

    Serial.end();
    return 0;
}
