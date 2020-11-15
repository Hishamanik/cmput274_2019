/*
   Places where you will modify/add code are indicated with **** in a comment

   To compile and run on the VM:
     g++ emailaddress.cpp -o emailaddress
     ./emailaddress

   If you compile outside the VM, you might need to add the flag -std=c++11
     g++ emailaddress.cpp -o emailaddress -std=c++11
*/

#include <iostream>
#include <cctype>

using namespace std;

enum EmailState {
  // **** you will have add more state names here!
  ID_INIT, ID, DOM1_INIT, DOM2, ERROR
};

bool check_address(const char* str) {
  EmailState state = ID_INIT;

  /*
    In the assignment, you would probably use a while loop that checks
    that the current state is not the "data exchange" state.

    For each state in the loop, you can wait until the required number
    of bytes are available (timing out if you wait too long) and then
    make the transition and perform the corresponding actions based
    on what was read.
  */
  for (int i = 0; str[i]; ++i) {

    // if the current state is ID_INIT, determine the state to move to
    if (state == ID_INIT) {
      // we only accept letters in this state
      if (isalpha(str[i])) { state = ID; }
      else { state = ERROR; }
    }
    else if (state == ID) {
      // letters or  '@' are permitted, each transitions to a different state
      if (isalpha(str[i])) { state = ID; }
      else if (str[i] == '@') { state = DOM1_INIT; }
      else { state = ERROR; }
    }

    // **** NOW YOU FINISH THIS!
    // Your goal is to have all tests below pass!

  }

  // **** Modify this to return true if and only if you ended
  //in the appropriate state.
  return true;
}

bool test_check_address_once(const char* str, bool expected) {
  cout << "Testing " << str << "... ";
  if (check_address(str) != expected) {
    cout << "incorrect output" << endl;
    return false;
  }
  else {
    cout << "OK!" << endl;
    return true;
  }
}

void test_check_address() {
  bool ok_tests = true;
  const char* badstrings[] = {
    "mistake@ualbertaca",
    "obviously.not.valid",
    "missing@dotcom",
    "bad!@punctiation.com",
    "@gmail.com",
    "email@.com",
    "email@gmail",
    "n0numbersfirst@gmail.com",
    "twodot@gmail..com"
  };

  const char* goodstrings[] = {
    "zac@ualberta.ca",
    "email@gmail.com",
    "a@b.c",
    "many@dots.are.allowed.you.know"
  };

  // This sort of for loop is a c++11 feature that is discussed in CMPUT 275.
  // It is a "range-based" for loop, like in Python.
  for (auto str : badstrings) {
    ok_tests &= test_check_address_once(str, false);
  }

  for (auto str : goodstrings) {
    ok_tests &= test_check_address_once(str, true);
  }


  cout << endl;
  if (ok_tests) {
    cout << "All tests passed!" << endl;
  }
  else {
    cout << "Some tests failed" << endl;
  }
}

int main() {
  test_check_address();

  return 0;
}