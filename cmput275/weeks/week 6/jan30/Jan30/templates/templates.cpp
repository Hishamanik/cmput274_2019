#include <iostream>

using namespace std;

struct myStruct {
  int x;
};

// returns the maximum of the two arguments
template <typename T>
T getMax(const T& a, const T& b) {
  if (a >= b) return a;
  else return b;
}

int main() {
  int a = getMax(10, 20);
  char b = getMax<char>('z', 'x');
  long long c = getMax(3ll, 5ll);
  int d = getMax<int>(70, 65);

  myStruct sa = {1}, sb = {2};
  // comiple error if you uncomment
  //myStruct sc = getMax<myStruct>(sa, sb);

  cout << a << ' ' << b << ' ' << c << ' ' << d << endl;

  return 0;
}
