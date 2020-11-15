// Name: Al Hisham Anik
// ID: 1585385
// CMPUT274, Fall 2019
//
//Exercise 5: Counting Lights


#include <Arduino.h>

int ledPins[5] = {9, 10, 11, 12, 13};
int ledMemory[5] = {LOW, LOW, LOW, LOW, LOW};
// pin 5 used for storing and recalling the current state, 6 used for increment, 7 for decrement
int Buttons[3] = {5, 6, 7};

//ledMemory2 is for storing and recalling the current state
int ledMemory2[5];

void setup(){
	init();
	Serial.begin(9600);
	int i;
	for (i=0; i<5; i++) {
		pinMode(ledPins[i], OUTPUT);
		digitalWrite(ledPins[i], ledMemory[i]);
	}
	int j;
	for (j=0; j<3; j++){
		pinMode(Buttons[j], INPUT);
		digitalWrite(Buttons[j], HIGH);
	}
}

int main() {
	setup();

	// The value 1 represents the state to be stored when we press the 'store/recall' button
	int recall = 1;
	while(true) {
		// This loop works does the job of increment of the pushbutton stored in list index 1
		if (digitalRead(Buttons[1]) == LOW){
			// program will be executed only when the buttons are released 
			while (digitalRead(Buttons[1]) == LOW) {
				delay(50);
			}
			bool constraint = false;
			int k = 0;
			while (constraint == false) {
				if (k==5) {
					constraint = true;
				} else if (ledMemory[k] == LOW) {
					ledMemory[k] = HIGH;
					constraint = true;
					digitalWrite(ledPins[k], ledMemory[k]);
				} else if (ledMemory[k] == HIGH) {
					ledMemory[k] = LOW;
					digitalWrite(ledPins[k], ledMemory[k]);
				}
				k++ ;
			}
		} else if (digitalRead(Buttons[2]) == LOW) {

			while (digitalRead(Buttons[2]) == LOW) {
				delay(50);
			}
			bool constraint = false;
			int k = 0;
			while (constraint == false) {
				if (k==5) {
					constraint = true;
				} else if (ledMemory[k] == HIGH){
					ledMemory[k] = LOW;
					constraint = true;
					digitalWrite(ledPins[k], ledMemory[k]);
				} else if (ledMemory[k] == LOW) {
					ledMemory[k] = HIGH;
					digitalWrite(ledPins[k], ledMemory[k]);
				}
				k++ ;
			}

		} else if (digitalRead(Buttons[0]) == LOW) {
			while (digitalRead(Buttons[0]) == LOW) {
				delay(50);
			}
			if (recall == 1) {
				// This loop stores the current state and turns all the LEDs OFF
				int i;
				for (i=0; i<5; i++) {
					ledMemory2[i] = ledMemory[i];
					digitalWrite(ledPins[i], LOW);
				}
				recall = 0;
			} else if (recall == 0) {
				// This loop recalls the sequence that was stored
				int j;
				for (j=0; j<5; j++) {
					ledMemory[j] = ledMemory2[j];
					digitalWrite(ledPins[j], ledMemory[j]);
				}
				recall = 1;

			}
		}
		delay(50);

	}
	return 0;
}











