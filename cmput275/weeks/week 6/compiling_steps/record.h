#ifndef _RECORD_H_
#define _RECORD_H_

#define MAX_NAME_LEN 15

// a struct to hold the name and mark of a single student
struct StudentRecord {
	char name[MAX_NAME_LEN+1];
	int mark;
};

// creates a struct with the students name and grade
// assumes the name is at most 15 characters long
StudentRecord createRecord(const char *name, int mark);

#endif
