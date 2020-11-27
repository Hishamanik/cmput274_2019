#include <iostream>
#include <cmath> // for sqrt

using namespace std;

// Compute the greatest integer d such that d*d <= n
// (i.e. the floor of the square root).
//
// You may use this function or ignore it, it's up to you.
unsigned int integer_sqrt(unsigned int x) {
  unsigned int d = sqrt(x);

  // should iterate at most once, probably none
  while ((d+1)*(d+1) <= x) {
    ++d;
  }

  // probably does not iterate even once
  while (d*d > x) {
    --d;
  }

  // now at this point we know (d+1)*(d+1) > x yet d*d <= x

  return d;
}

int main() {
  // declare your variables
  uint number ;
  int x =0;
  int sum =0;

  // read the input
  cin >> number ;

  // solve the problem

  if (number == 0){
    cout << "sum of squares" << endl ;
  }
  else {
    unsigned root = sqrt(number);
    cout << root;
    for (uint32_t i=0; i<root+1; i++) {
      for(uint32_t j=1; j<root+1 ; j++){
        sum = (j*j)+(i*i) ;
        if (sum == number){
          cout << "sum of squares" << endl;
          x = 1;
          j= root;
          i =root;
        }
      }
    }
  }

  // print the answer
  if (x==0 && number != 0){
    cout << "not sum of squares" << endl ;
  }

  return 0;
}
