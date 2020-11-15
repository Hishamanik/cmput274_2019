// Name: Al Hisham Anik
// ID: 1585385
// CMPUT274, Fall 2019
//
//Exercise 6: Serial Counter

#include <Arduino.h>

//setting global variable for LED array
int const ledPins[5] = {9, 10, 11, 12, 13};


void setup() {
	init();
	//This is used to communicate with the PC
	Serial.begin(9600);
	//Initializing pins
	int i;
	for (i=0; i<5; i++) {
		pinMode(ledPins[i], OUTPUT);
		digitalWrite(ledPins[i], LOW);
	}
}

// returns the value of Hexadecimal digit both lower and upper case
// Other character outside hexadecimal is not effected
int8_t getHexValue(char digit) {
	if (digit>= '0' && digit <= '9') {
		return digit-'0';
	} else if (digit>='a' && digit<= 'f') {
		return 10 + (digit-'a');
	} else if (digit>= 'A' && digit<= 'F') {
		return 10 + (digit-'A');
	// return digit is not a hexadecimal digit no effect occurs
	} else { 
		return -1;
	}
}

// Updates the 5 LEDs to illuminate the 5 least significant bit total
void updateLEDs(uint8_t total) {
	uint8_t bit = 1;
	int pin = 0;
	// This goes over the 5 LSB
	for (bit; bit<=16; bit<<=1) {
		// This tells us whether bit at position 'pin' is 0 or 1
		if (total & bit) {
			digitalWrite(ledPins[pin], HIGH);
		} else {
			digitalWrite(ledPins[pin], LOW);
		}
		pin++;
	}
}

// Main Function
int main() {
	setup();
	uint8_t total = 0;
	while (true) {
		if (Serial.available()>0) {
			char digit = Serial.read();
			// This resets to 0 whenever a spacebar or return key is pressed
			if (digit==' ' || digit=='\r') { 
				total = 0;
				updateLEDs(total);
			} else {
				int8_t updater = getHexValue(digit);
				if (updater!= -1) {
					total += updater;
					updateLEDs(total);
				}
			}
		}
	}
	// flushes off buffered messages
	Serial.flush();
	return 0;
}