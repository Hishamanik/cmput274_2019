/*
	Test program for raw SD card data. Will print the name of a
	few restaurants to the serial monitor, assuming the SD card was
	formatted properly in class.
*/

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <MCUFRIEND_kbv.h>

#define SD_CS 10

const uint32_t REST_START_BLOCK = 4000000;
const uint32_t BYTES_PER_BLOCK = 512;

// Use hardware SPI (on Mega2560, #52, #51, and #50) and the above for CS/DC
MCUFRIEND_kbv tft;

Sd2Card card;

void setup() {
	init();

	Serial.begin(9600);

 	// must initialize even when using SD card only
	tft.begin(tft.readID());

	Serial.print("Initializing SD card...");
	if (!SD.begin(SD_CS)) {
		Serial.println("failed!");
		Serial.println("Is the card inserted properly?");
		while (true) {}
	}
	Serial.println("OK");

	Serial.print("Initializing SPI communication for raw reads...");
	if (!card.init(SPI_HALF_SPEED, SD_CS)) {
		Serial.println("failed!");
	  while (true) {}
	}

	Serial.println("OK");
	Serial.println();
}

int main() {
	setup();

	//512 is the number of b
	uint8_t data[BYTES_PER_BLOCK];
	while (!card.readBlock(REST_START_BLOCK, data)) {
		Serial.println("SD card readBlock fail... trying again.");
	}

	// each restaurant's data is 64 bytes long
	// the name is offset 9 bytes from the start of the data
	// and is already null-terminated
	for (int i = 0; i < 8; ++i) {
		Serial.println((char*) (data+9+i*64));
	}

	Serial.end();
	return 0;
}
