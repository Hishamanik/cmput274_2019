/*
  Print a null-terminated string backwards using recursion.
*/

#include <iostream>

using namespace std;

// To print the string backward, use recursion to print the
// remaining characters backward and then print the one
// being pointed at.
void printBackward(const char* str) {
  // *str will be the ASCII value of the character being pointed at
  // by this pointer. If it is the null terminator (i.e. the 0 byte)
  // then this evaluates to false, otherwise it evaluates to true.
  if (*str) {
    // so if the character was not the null terminator, print the rest of
    // the string backward recursively
    printBackward(str+1); // uses pointer arithemtic
    cout << (*str); // now print this character
  }
}

int main() {
  printBackward("hello");
  cout << endl;

  return 0;
}
