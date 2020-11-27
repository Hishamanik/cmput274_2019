#ifndef __COUNTER_H_
#define __COUNTER_H_

// Working time challenge.
// Add a reset() method that will reset curr_value to the
//   initial value. You will have to store the initial value
//   in the class as well.
// If you finish this, try the following:
//  1) Add a Makefile with different targets for the two .o files
//     for the cpp files and a target to link them.
//  2) Research operator overloading to add the ++ and -- operators
//     to this class (eg, so you can say myCounter++ or myCounter--)
//     to increment and decrement).

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

private:
  // Hide these from the user because we want to maintain
  // curr_value is in the range. The user can only interact
  // with them using the methods we provide.
  int curr_value, range_low, range_high;
};

#endif
