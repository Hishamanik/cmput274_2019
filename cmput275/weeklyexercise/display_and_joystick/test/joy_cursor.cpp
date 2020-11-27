// Name: Al Hisham Anik
// ID: 1585385
// CMPUT275, Winter 2020
//
//Reference: starter code used from eclass
//Exercise 1: Display and Joystick

/*
	Demonstrating cursor movement over the map of Edmonton. You will improve over
  what we do in the next weekly exercise.
*/

#define SD_CS 10
#define JOY_VERT  A9 // should connect A9 to pin VRx
#define JOY_HORIZ A8 // should connect A8 to pin VRy
#define JOY_SEL   53

#include <Arduino.h>

// core graphics library (written by Adafruit)
#include <Adafruit_GFX.h>

// Hardware-specific graphics library for MCU Friend 3.5" TFT LCD shield
#include <MCUFRIEND_kbv.h>

// LCD and SD card will communicate using the Serial Peripheral Interface (SPI)
// e.g., SPI is used to display images stored on the SD card
#include <SPI.h>

// needed for reading/writing to SD card
#include <SD.h>

#include "lcd_image.h"


MCUFRIEND_kbv tft;

#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320
#define YEG_SIZE 2048

lcd_image_t yegImage = { "yeg-big.lcd", YEG_SIZE, YEG_SIZE };

#define JOY_CENTER   512
#define JOY_DEADZONE 64

#define CURSOR_SIZE 9

// the cursor position on the display
int cursorX, cursorY;

// forward declaration for redrawing the cursor
void redrawCursor(uint16_t colour);

void setup() {
  init();

  Serial.begin(9600);

	pinMode(JOY_SEL, INPUT_PULLUP);

	//tft.reset();                  // hardware reset
  uint16_t ID = tft.readID();    // read ID from display
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  
  // must come before SD.begin() ...
  tft.begin(ID);                 // LCD gets ready to work

	Serial.print("Initializing SD card...");
	if (!SD.begin(SD_CS)) {
		Serial.println("failed! Is it inserted properly?");
		while (true) {}
	}
	Serial.println("OK!");

	tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);

  // draws the centre of the Edmonton map, leaving the rightmost 60 columns black
	int yegMiddleX = YEG_SIZE/2 - (DISPLAY_WIDTH - 60)/2;
	int yegMiddleY = YEG_SIZE/2 - DISPLAY_HEIGHT/2;
	lcd_image_draw(&yegImage, &tft, yegMiddleX, yegMiddleY,
                 0, 0, DISPLAY_WIDTH - 60, DISPLAY_HEIGHT);

  // initial cursor position is the middle of the screen
  cursorX = (DISPLAY_WIDTH - 60)/2;
  cursorY = DISPLAY_HEIGHT/2;

  redrawCursor(TFT_RED);

}

void redrawCursor(uint16_t colour) {
  tft.fillRect(cursorX - CURSOR_SIZE/2, cursorY - CURSOR_SIZE/2,
               CURSOR_SIZE, CURSOR_SIZE, colour);  
}


void processJoystick() {
  int xVal = analogRead(JOY_HORIZ);
  int yVal = analogRead(JOY_VERT);
  int buttonVal = digitalRead(JOY_SEL);

  //redrawCursor(TFT_BLACK);
  int yegMiddleX = YEG_SIZE/2 - (DISPLAY_WIDTH - 60)/2;
  int yegMiddleY = YEG_SIZE/2 - DISPLAY_HEIGHT/2;

  // decrease the y coordinate of the cursor as joytick moves up
  if (yVal < JOY_CENTER - JOY_DEADZONE) {
    //lcd_image draw function draws a small patch of the Edmonton map 
    //at the old cursor position before
    lcd_image_draw(&yegImage, &tft,
     // upper left corner in the image to draw
     yegMiddleX + (cursorX- CURSOR_SIZE/2), yegMiddleY + (cursorY- CURSOR_SIZE/2),
     // upper left corner of the screen to draw it in
     cursorX - CURSOR_SIZE/2, cursorY -CURSOR_SIZE/2,
     // width and height of the patch of the image to draw
     CURSOR_SIZE, CURSOR_SIZE);

    //Subtracting from a  constant number to make the cursor increases speed
    //when the joystick is pushed further
    cursorY -= (JOY_CENTER/50 - yVal/50); // 
    cursorY = constrain(cursorY, 4, DISPLAY_HEIGHT-4);

    redrawCursor(TFT_RED); //draws a red rectangle at the new cursor position  
  }

  else if (yVal > JOY_CENTER + JOY_DEADZONE) {
    //lcd_image draw function draws a small patch of the Edmonton map 
    //at the old cursor position before
    lcd_image_draw(&yegImage, &tft,
     yegMiddleX + (cursorX- CURSOR_SIZE/2), yegMiddleY + (cursorY- CURSOR_SIZE/2),
     cursorX - CURSOR_SIZE/2, cursorY -CURSOR_SIZE/2,
     CURSOR_SIZE, CURSOR_SIZE);   
  
    cursorY += yVal/50 ;
    cursorY = constrain(cursorY, 4, DISPLAY_HEIGHT-4);

    redrawCursor(TFT_RED); 
  }
    
    

  //the x-reading decreases as we push left
  if (xVal > JOY_CENTER + JOY_DEADZONE) {
    //lcd_image draw function draws a small patch of the Edmonton map 
    //at the old cursor position before
    lcd_image_draw(&yegImage, &tft,
     yegMiddleX + (cursorX- CURSOR_SIZE/2), yegMiddleY + (cursorY- CURSOR_SIZE/2),
     cursorX - CURSOR_SIZE/2, cursorY -CURSOR_SIZE/2,
     CURSOR_SIZE, CURSOR_SIZE); 
    
    cursorX -= xVal/50;
    cursorX = constrain(cursorX, 4.5, DISPLAY_WIDTH-65);
    
    redrawCursor(TFT_RED);


  }

  //x-reading increases as we push right
  else if (xVal < JOY_CENTER - JOY_DEADZONE) {
    //lcd_image draw function draws a small patch of the Edmonton map 
    //at the old cursor position before
    lcd_image_draw(&yegImage, &tft,
     yegMiddleX + (cursorX- CURSOR_SIZE/2), yegMiddleY + (cursorY- CURSOR_SIZE/2),
     cursorX - CURSOR_SIZE/2, cursorY -CURSOR_SIZE/2,
     CURSOR_SIZE, CURSOR_SIZE); 

    //Subtracting from a  constant number to make the cursor increases speed
    //when the joystick is pushed further
    cursorX += (JOY_CENTER/50 - xVal/50);
    cursorX = constrain(cursorX, 4.5, DISPLAY_WIDTH-65);
    
    redrawCursor(TFT_RED);
  }


  delay(50);
}


int main() {
	setup();

  while (true) {
    processJoystick();
  }

	Serial.end();
	return 0;
}