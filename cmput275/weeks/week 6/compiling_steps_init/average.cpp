#include "average.h"
#include "record.h"

double calcAverage(StudentRecord students[], int num) {
	double avg = 0;
 	for (int i = 0; i < num; i++) {
	 	avg += students[i].mark;
 	}
 	return avg/num;
}
