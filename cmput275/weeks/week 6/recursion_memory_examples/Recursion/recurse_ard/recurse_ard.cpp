/*
	A demonstration of what could happen if recursion goes too deep on an Arduino.
*/

#include "Arduino.h"

int factorial(int n) {
	if (n == 0) {
		return 1;
	}
	else {
		Serial.print(n);
		Serial.print(" ");
		// print the address of parameter n (which is also a local variable)
		// we cast to 16-bit integer types because pointers on an Arduino
		// are 16 bits long
		Serial.println((uint16_t)(&n));
		return n*factorial(n-1);
	}
}

void setup() {
	init();
	Serial.begin(9600);
}

int main(){
  // too deep, will cause a bug!
	// the stack collides with the heap/data section and things
	// become unpredictable
	int fact = factorial(1500);

	Serial.print("Factorial: ");
	Serial.println(fact);

	Serial.flush();
	return 0;
}
