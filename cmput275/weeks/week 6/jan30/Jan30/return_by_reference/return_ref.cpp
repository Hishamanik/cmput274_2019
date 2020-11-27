// Some simple examples of return by reference.

#include <iostream>

using namespace std;

int globalVal;

// Returns an alias of the variable globalVal.
int& returnGlobal() {
  return globalVal;
}

// Very dangerous! We returned a reference to memory on the stack,
// but the variable goes out of scope so the space to store the variable.
// If we use this, we probably get a segfault because we indexed outside of
// the stack.
int& dangerous() {
  int localVar = 17;
  return localVar;
}

int main() {
  globalVal = 7;

  cout << "Global: " << globalVal << endl;

  // Looks super strange! The reason is that the return type
  // is actually reference to an actual variable, so it can be treated as
  // assignable
  returnGlobal() = 13;
  cout << "Global: " << globalVal << endl;

  int& danger = dangerous();

  // should cause a segfault
  cout << danger << endl;

  return 0;
}
