/*
  Recursive code that prints moves for solving the Towers of Hanoi challenge.
*/

#include <iostream>

using namespace std;

void solveHanoi(int k, int start, int end, int inter) {
  if (k == 0) {
    // nothing to move
    return;
  }

  // move the k-1 topmost disks to the intermediate peg
  solveHanoi(k-1, start, inter, end);
  // move the largest disk to the end peg
  cout << "Move disk " << k << " to peg " << end << endl;
  // finally, move the remaining k-1 disks to the end peg
  solveHanoi(k-1, inter, end, start);
}

int main() {
  // move k disks from peg 1 to peg 3
  int k;
  cout << "Enter number of disks: ";
  cin >> k;
  solveHanoi(k, 1, 3, 2);

  return 0;
}
