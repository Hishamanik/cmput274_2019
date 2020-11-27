/*
  Implementation of an array that can be resized during run time.

  We didn't separate the declaration from the implementation in
  .h and .cpp files because this is template code. Unfortunately,
  template code cannot be put in a standalone .cpp file.
*/

#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

#include <cassert>
#include <cstdlib>

using namespace std;

// A dynamic array that can be resized
// when desired.
template <typename T>
class DynamicArray {
public:
  // create a new array with the given size
  DynamicArray(unsigned int size = 0);

  // TODO: the destructor isn't finished
  ~DynamicArray();

  // add a new entry to the end of the array
  void pushBack(const T& item);

  // TODO: You implement this!
  // Decrease the number of items by 1 by removing the last item.
  // Try a "quartering" trick: if only 1/4 of the array is used then
  // resize it so it is 1/2 full.
  void popBack();

  // resize the array, keeping the items in the current array
  // except for ones that are indexed >= size
  void resize(unsigned int newSize);

  // have the array hold "item" at the given index
  void setItem(unsigned int index, const T& item);

  // get a copy of the item at the given index
  T getItem(unsigned index) const;

  unsigned int size() const;

private:
  T *array; // the allocated space in the heap
  unsigned int numItems;  // number of items in the array, for the user
  unsigned int arraySize; // size of the underlying array in the heap
};

template <typename T>
DynamicArray<T>::DynamicArray(unsigned int size) {
  // store the initial size of the array
  numItems = size;

  // no array yet, we'll get it from resize()
  array = NULL;
  resize(numItems);
}

template <typename T>
void DynamicArray<T>::resize(unsigned int newSize) {
  // get an array of twice the new size (or 5, if the new size is really small)
  unsigned int newArraySize = max(newSize*2, 5u);
  T *newArray = new T[newArraySize];

  if (array != NULL) {
    // copy the old array over, until the new size
    for (unsigned int i = 0; i < min(numItems, newSize); i++) {
      newArray[i] = array[i];
    }
    delete[] array;
  }

  // update the class members for this new array
  // and point to it now
  numItems = newSize;
  arraySize = newArraySize;
  array = newArray;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  // you should do something here to prevent a memory leak...
}

template <typename T>
void DynamicArray<T>::setItem(unsigned int index, const T& item) {
  assert(0 <= index && index < numItems);
  array[index] = item;
}

template <typename T>
T DynamicArray<T>::getItem(unsigned int index) const {
  assert(0 <= index && index < numItems);
  return array[index];
}

template <typename T>
unsigned int DynamicArray<T>::size() const {
  return numItems;
}

template <typename T>
void DynamicArray<T>::pushBack(const T& item) {
  if (numItems == arraySize) {
    resize(numItems+1);
    // we haven't put the new item in yet
    numItems--;
  }
  array[numItems] = item;
  numItems++;
}

#endif
