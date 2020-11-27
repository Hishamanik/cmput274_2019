/*
  A simple demonstration of recursion (computing factorials)
  and highlighting memory addresses of a few variables
  (global and local).
*/

#include <iostream>

using namespace std;

// global variables are in the ``data'' section, as such
// they have a considerably lower address than variables on
// the stack
int global_var = 5;

int factorial(int n) {
  if (n == 0) {
    return 1;
  }
  else {
    int a = factorial(n-1);
    cout << "Address of a for factorial(" << n << ") = ";
    // cast to a 64-bit type because pointers are 64 bits long
    // on a 64-bit OS
    cout << (unsigned long long)(&a) << endl;
    // can also do cout << (&a) << endl;
    // to see the address of the local variable in hexS
    return a*n;
  }
}

int main() {
  // cout << "5! = " << factorial(5) << endl;

  cout << "Global var address: " << (&global_var) << endl;
  factorial(5);

  // the following causes the stack to overflow which will
  // cause the program to crash (on the VM)
  // factorial(1000000)

  return 0;
}
