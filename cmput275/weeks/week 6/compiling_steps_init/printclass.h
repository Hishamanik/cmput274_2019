#ifndef _PRINTCLASS_H_
#define _PRINTCLASS_H_

#include <iostream>
#include <iomanip> // for setw
#include "record.h"

using namespace std;

// generally we don't like to code in a header file,
// but you will see it sometimes so here is an example

// prints all students with their grades
// it is defined this .h file, no .cpp (just to show you
// this sometimes happens)
void printClassList(StudentRecord students[], int num) {
	for (int i = 0; i < num; i++) {
		cout << setw(16) << left << students[i].name
				 << students[i].mark << endl;
	}
}

#endif
