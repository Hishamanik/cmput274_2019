#include "record.h"
#include <cstring> // for strcpy
#include <cassert>

using namespace std;

// creates a struct with the students name and grade
// assumes the name is at most 31 characters long
StudentRecord createRecord(const char *name, int mark) {
	StudentRecord student;

	// can only fit 15-character names in the struct
	assert(strlen(name) <= MAX_NAME_LEN);

	// copy all characters from the string "name"
	// into student.name (including the null terminator)
	strcpy(student.name, name);
	student.mark = mark; 

	return student;
}
