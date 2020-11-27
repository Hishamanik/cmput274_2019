#include <iostream>
#include "counter.h"

using namespace std;

void aFunction() {
  Counter counterFn(7, 2, 13);
  cout << "We constructed it!" << endl;
}

Counter returnCounter() {
  Counter cnt(11, 10, 12);
  return cnt;
}

int main() {
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

  Counter nxtCount = returnCounter();
  cout << nxtCount.getCurrValue() << endl;

  cout << "Start" << endl;
  if (true) {
    Counter tmpCount(7, 1, 14);
  }
  cout << "End" << endl;

  return 0;
}
