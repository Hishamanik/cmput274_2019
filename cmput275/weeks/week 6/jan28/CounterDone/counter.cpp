#include "counter.h" // so we know the class definition

#include <cassert>
#include <iostream>

using namespace std;

Counter::Counter(int init_value, int range_low, int range_high) {
  //curr_value, range_low, range_high;

  assert(range_low <= init_value && init_value <= range_high);

  // "this" is a pointer to this instance of the class
  // so dereferencing it with * gives the actual instance
  // and now we can access its members with . (just like a struct)

  // for a pointer ptr pointing to something with a .x variable,
  // (*ptr).x is the same as ptr->x
  this->init_value = init_value;
  this->range_low = range_low;
  this->range_high = range_high;

  // might as well use reset to set the initial value
  reset();

  cout << "Constructor called: " << init_value << ' '
       << range_low << ' ' << range_high << endl;
}

Counter::~Counter() {
  // does nothing here, not very useful in this case
  // but it will be next lecture!

  cout << "Destructor called: " << curr_value << ' '
       << range_low << ' ' << range_high << endl;
}

bool Counter::increment() {
  // can refer directly to the class member because
  // nothing overshadows the name of the member
  if (curr_value < range_high) {
    ++curr_value;
    return true;
  }
  else {
    return false;
  }
}

bool Counter::decrement() {
  if (curr_value > range_low) {
    --curr_value;
    return true;
  }
  else {
    return false;
  }
}

int Counter::getCurrValue() const {
  return curr_value;
}

void Counter::reset() {
  curr_value = init_value;
}

Counter Counter::operator++(int) {
  Counter old = *this;
  this->increment();
  return old;
}

Counter Counter::operator--(int) {
  Counter old = *this;
  this->decrement();
  return old;
}
