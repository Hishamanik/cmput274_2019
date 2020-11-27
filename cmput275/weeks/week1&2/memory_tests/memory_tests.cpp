/*
	Just some examples of how to use pointers, aliases,
	references, and dereferences.
*/

#include <Arduino.h>

void setup() {
	init();
  Serial.begin(9600);
}

int some_global = 7;

void function2() {
	uint32_t a = 4;
	Serial.print("Function 2 local variable: ");
	Serial.println((uint16_t) &a);
}

void function1() {
	uint32_t a = 7;
	function2();
	Serial.print("Function 1 local variable: ");
	Serial.println((uint16_t) &a);
	function2();
}

void doubling(uint32_t &a) {
	a *= 2;
}

int main() {
	setup();

	uint32_t a = 5, b = 17;
	uint32_t *ptr = &a;

	Serial.print("Local variable: ");
	Serial.println((uint16_t) ptr);

	Serial.print("Global variable: ");
	Serial.println((uint16_t) &some_global);

	function1();
	function2();

	*ptr = a+7;
	Serial.print("Value of a: ");
	Serial.println(a);

	ptr = &b;
	Serial.print("Local pointer: ");
	Serial.println((uint16_t) ptr);
	*ptr = 1;
	Serial.print(a);
	Serial.print(" ");
	Serial.println(b);

	uint32_t var = 12345;
	uint32_t &alias = var;
	alias = 878;
	Serial.print("Var and Alias: ");
	Serial.print(var);
	Serial.print(" ");
	Serial.println(alias);
	Serial.print("Address of var and alias: ");
	Serial.print((uint16_t) &var);
	Serial.print(" ");
	Serial.println((uint16_t) &alias);

	uint32_t small_val = 2;
	doubling(small_val);
	Serial.println(small_val);

	uint32_t array[] = {1, 5, 6, 9};
	uint32_t *aptr = &array[1];
	aptr += 2;
	Serial.println(*aptr);

	Serial.end();

  return 0;
}
