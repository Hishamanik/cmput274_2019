#include <iostream>
#include "dynarray.h"

using namespace std;

void dumpArray(const DynamicArray<int> &a) {
  cout << "Size is: " << a.size() << endl;
  cout << "Items:";
  for (unsigned int i = 0; i < a.size(); i++) {
    cout << ' ' << a.getItem(i);
  }
  cout << endl;
}

int main() {
  DynamicArray<int> a(10);

  dumpArray(a);

  for (unsigned int i = 0; i < a.size(); i++) {
    a.setItem(i, 2*i);
  }

  dumpArray(a);

  a.resize(7);

  for (int i = 0; i < 20; i++) {
    a.pushBack(101+i);
  }

  dumpArray(a);

  cout << a[0] << endl;
  a[0] = a[1] + a[2];
  cout << a[0] << endl;

  return 0;
}
