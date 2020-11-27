#include <iostream>
#include <iomanip> // for setw and setfill
#include "average.h"
#include "printclass.h"
#include "record.h"

#define NUMRECORDS 5

using namespace std;

int main() {
	StudentRecord students[NUMRECORDS];

	students[0] = createRecord("Zac", 82);
	students[1] = createRecord("Omid", 93);
	students[2] = createRecord("Neural Network", 17);
	students[3] = createRecord("Cat", 99);
	students[4] = createRecord("Turnip", 0);

	printClassList(students, NUMRECORDS);
	cout << setfill('-') << setw(19) << "" << endl;

	cout << "Average mark:   " << calcAverage(students, NUMRECORDS) << endl;

	return 0;
}
