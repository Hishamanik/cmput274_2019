#include <iostream>
#include <iomanip>
#include <cassert>
#include "hash_table.h"

using namespace std;

struct StudentRecord {
  char name[20];
  unsigned int id;
  unsigned int grade;

  // returns a hash of the student struct
  // in this case, we simply return the id which seems very natural
  // as student IDs are (roughly) consecutive so they will be distributed
  // roughly evenly between buckets
  unsigned int hash() const;

  // two records with the same ID will be regarded as the same
  bool operator==(const StudentRecord& rhs) const;
  bool operator!=(const StudentRecord& rhs) const;
};

unsigned int StudentRecord::hash() const {
  return id;
}

bool StudentRecord::operator==(const StudentRecord& rhs) const {
  return id == rhs.id;
}

bool StudentRecord::operator!=(const StudentRecord& rhs) const {
  return id != rhs.id;
}




int main() {
  // create a new table with 20 buckets
  HashTable<StudentRecord> table(20);

  StudentRecord students[] = {
    {"Zac",  12345, 76},
    {"Omid", 87654, 76},
    {"Alexa", 80000, 70},
    {"Siri",  55545, 84}
  };

  table.insert(students[0]);
  table.insert(students[2]);

  table.insert(students[3]);

  assert(table.contains(students[2]) == true);
  assert(table.contains(students[1]) == false);

  table.remove(students[0]);
  table.insert(students[1]);

  assert(table.contains(students[0]) == false);
  assert(table.contains(students[1]) == true);

  table.insert(students[0]);

  assert(table.contains(students[0]) == true);

  return 0;
}
