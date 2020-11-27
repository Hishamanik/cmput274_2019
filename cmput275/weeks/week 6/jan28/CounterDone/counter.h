#ifndef __COUNTER_H_
#define __COUNTER_H_

/*
  A counter that you can increment and decrement,
  but it stays clamped inside a range.
*/
class Counter {
public:

  // expects init_value to lie in the given range
  // default is starting at 0 with a range [0, 100]
  Counter(int init_value = 0, int range_low = 0, int range_high = 100);
  ~Counter(); // destructor

  // increment the counter, but stay in the range
  // return true iff it actually incremented
  bool increment();

  // decrement the counter, but stay in the range
  // return true iff it actually decremented
  bool decrement();

  // return the current value (a copy of it)
  // const is a promise that nothing in the class will change
  int getCurrValue() const;

  // reset the counter to the initial value
  void reset();

  // postfix increment/decrement operators overloaded
  // the "int" parameter is required to distinguis this from the prefix version
  // do more research to see how to overload the prefix --/++ operators
  Counter operator++(int);
  Counter operator--(int);

private:
  // Hide these from the user because we want to maintain
  // curr_value is in the range. The user can only interact
  // with them using the methods we provide.
  int curr_value, range_low, range_high, init_value;
};

#endif
