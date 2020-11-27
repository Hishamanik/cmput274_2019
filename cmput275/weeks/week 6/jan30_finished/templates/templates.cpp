#include <iostream>

using namespace std;

// by overloading the < operator, we can even use this type "myStruct"
// as the template parameter for the getMax function
struct myStruct {
  int x;
  bool operator<(const myStruct& rhs) const;
};

bool myStruct::operator<(const myStruct& rhs) const {
  return x < rhs.x;
}

// returns the maximum of the two arguments
template <typename T>
T getMax(const T& a, const T& b) {
  // cout << a << ' ' << b << ' ' << sizeof(a) << endl;
  if (b < a) return a;
  else return b;
}

template <typename S, typename T>
void printBoth(const S& a, const T& b) {
  cout << a << ' ' << b << endl;
}

int main() {
  int a = getMax(10, 20);
  char b = getMax<char>('z', 'x');
  long long c = getMax(3ll, 5ll);
  int d = getMax<int>(70, 65);

  // compile error, types don't match
  //int e = getMax(15, 20ll);

  myStruct sa = {1}, sb = {2};

  myStruct sc = getMax<myStruct>(sa, sb);
  cout << sc.x << endl;

  cout << a << ' ' << b << ' ' << c << ' ' << d << endl;

  printBoth<int, const char*>(14, "hello");

  return 0;
}
