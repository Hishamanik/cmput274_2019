#include <iostream>
#include "counter.h"

using namespace std;

// Demonstrates that the destructor is called at the end of this function
// because the variable falls out of scope.
void aFunction() {
  Counter counterFn(7, 2, 13);
  cout << "We constructed it!" << endl;
}

// Can return an instance of the counter from a function: it's just like
// returning a copy of a variable.
Counter returnCounter() {
  Counter cnt(11, 10, 12);
  return cnt;
}

int main() {
  // Try uncommenting various lines here to see what they do.

  // a counter with range [1,10] that
  // starts at value 9
  // Counter myCounter(9, 1, 10);
  //
  // cout << myCounter.getCurrValue() << endl;
  //
  // cout << myCounter.increment() << endl;
  // cout << myCounter.getCurrValue() << endl;
  //
  // cout << myCounter.increment() << endl;
  // cout << myCounter.getCurrValue() << endl;
  //
  // Counter anotherCounter;
  // cout << anotherCounter.getCurrValue() << endl;

  // cout << "Before constructor" << endl;
  // Counter yetAnother(3,1,5);
  // cout << "After constructor" << endl;
  //
  // cout << "Before function" << endl;
  // aFunction();
  // cout << "After function" << endl;

  // Counter nxtCount = returnCounter();
  // cout << nxtCount.getCurrValue() << endl;
  //
  // cout << "Start" << endl;
  // if (true) {
  //   Counter tmpCount(7, 1, 14);
  // }
  // cout << "End" << endl;

  Counter *clocks = new Counter[5]; // calls the constructor for each

  cout << "Clocks constructed!" << endl;

  delete[] clocks; // calls the destructor for each

  cout << "Clocks deleted!" << endl;

  // Testing reset function

  Counter clock(5, 1, 14);

  // Testing increment and decrement operators
  // Note, the way these work will temporarily create a copy
  // of the Counter class so the constructor/destructor cout statements
  // will be called a lot.
  clock++;
  clock++;
  clock++;
  clock--;

  cout << "Value: " << clock.getCurrValue() << endl;

  clock.reset();

  cout << "After reset: " << clock.getCurrValue() << endl;

  return 0;
}
