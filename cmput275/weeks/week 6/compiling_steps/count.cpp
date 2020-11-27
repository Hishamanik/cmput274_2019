#include "count.h"
#include "average.h"

int aboveAverage(StudentRecord students[], int num) {
  double avg = calcAverage(students, num);

  int numAbove = 0;
  for (int i = 0; i < num; i++) {
    if (students[i].mark > avg) {
      numAbove++;
    }
  }

  return numAbove;
}
