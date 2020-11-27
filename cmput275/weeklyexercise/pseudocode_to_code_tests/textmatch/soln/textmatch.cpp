// Name: Al Hisham Anik
// ID: 1585385
// CMPUT275, Winter 2020
// Refrence: I used the pseduo-code posted in weekly assignment3 to write my code 
// Exercise 3: Pseudocode to Code

//declaring libraries
#include <iostream>
#include <cstring> // for strlen()

using namespace std;

//accepts two character arrays(s,t)  holding null-terminated strings and prints all of the indices 0 ≤ i < length(t) 
//such that it appears as a substring of the starting at index of it.
void textMatch(const char *s, const char *t) {
	
	//determining the length of substring and string
	int length_of_t = strlen(t);
	int length_of_s = strlen(s);

	//initializing array(step) of maximum size that would be tested
	int step [100000];

	//computes an array step[] where step[i] is the largest k such that the first k+1 characters of s[0...i] 
	//and the last k+ 1 characters of s[0...i] form the same string
	step[0] = -1;
	int k = -1;
	for (int i=1; i<length_of_s; i++){
		while (k >=0 && s[k+1] != s[i]) {
			k = step[k] ;
		}
		if (s[k+1] == s[i]) {
			k = k+1 ;
		}
		step[i] = k;
	}

	//uses step[] to find all occurrences of s as a substring of t.  It does this by maintaining values m and i. 
	//At the start of each iteration of the outer loop,m will be the greatest integer such that the substrings[0. . . m] matches t[i−m−1. . . i−1]. 
	int m =-1;
	for (int i=0; i<length_of_t; i++){
		while (m>=0 && s[m+1]!=t[i]){
			m = step[m];
		}
		// It tries to match the next character (i.e. checks if s[m+ 1] =t[i]), if it cannot it steps m back to the “next” possible match at position step[m] 
		if (s[m+1]==t[i]){
			m = m+1;
		}
		//and repeats the check until eithers[m+ 1] = t[i] or m=−1
		if (m==(length_of_s-1)){
			cout << (i+1- length_of_s) << " " ;
			m = step[m];
		}
	}
	cout << endl;
}

//Main function
int main() {
	//declaring variables
	char s[100000];
	char t[100000];

	//reading input from terminal
	cin >> s;
	cin >> t;

	//calling function textMatch to find the index of the array of t for the appearance of substring s
	textMatch(s,t);


  return 0;
}
