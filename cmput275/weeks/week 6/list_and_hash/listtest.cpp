#include <iostream>
#include "linked_list.h"

using namespace std;


// Function to print the entire contents of a linked list (and the list size).
template <typename T>
void printList(LinkedList<T>& list) {
  cout << "List size: " << list.size() << endl;
  cout << "Contents:";

  for (ListNode<T> *node = list.getFirst(); node != NULL; node = node->next) {
    cout << ' ' << node->item;
  }

  cout << endl << endl;
}

void testRemove() {
  cout << "testRemove()" << endl;
  int array[] = {1, 1, 2, 1, 3, 1, 4, 1};
  LinkedList<int> list;

  // build the list
  for (int i = 0; i < 8; ++i) {
    list.insertBack(array[i]);
  }

  // remove the 2
  list.remove(2);
  assert(list.find(2) == NULL);
  printList(list);

  // remove all occurrences of 1
  list.removeAll(1);
  assert(list.find(1) == NULL);
  printList(list);

  cout << "done testRemove()" << endl << endl;
}

void testInsertBack() {
  cout << "testInsertBack()" << endl;
  LinkedList<char> list;

  const char* str = "hello";

  // go until we hit the null terminator
  for (int i = 0; str[i]; ++i) {
    list.insertBack(str[i]);
  }

  printList(list);

  ListNode<char>* link = list.find('e');
  list.insertAfter('s', link);

  printList(list);

  cout << "done testInsertBack()" << endl << endl;
}

int main() {
  testInsertBack();
  testRemove();

  cout << "now running remaining tests" << endl;

  LinkedList<int> list;

  // insert these items into the list using insertFront,
  // so the resulting list is in reverse order
  int insertList[] = {1, 1, 5, 3, 1, 7, 14, 6, 5};
  for (int i = 0; i < 9; i++) {
    list.insertFront(insertList[i]);
  }

  // print the list
  printList(list);

  // check that 8 is not in the list
  ListNode<int> *ptr = list.find(8);
  assert(ptr == NULL);

  // check that 5 is in the list
  ptr = list.find(5);
  assert(ptr != NULL && ptr->item == 5);

  // check removing a link
  list.removeNode(ptr);
  printList(list);

  // there should be another copy of 5, so check that it is in the list
  // and remove it
  ptr = list.find(5);
  assert(ptr != NULL && ptr->item == 5);
  list.removeNode(ptr);
  printList(list);

  // should have removed all 5s by now
  assert(list.find(5) == NULL);

  // insert 17 just before the 14
  ptr = list.find(14);
  assert(ptr != NULL && ptr->item == 14);
  list.insertBefore(17, ptr);
  printList(list);

  // now pop all but one item from the list, leaving only the first item
  while (list.size() > 1) {
    list.removeBack();
  }
  printList(list);

  // make sure it was the 6 that we left and remove it
  ptr = list.find(6);
  assert(ptr != NULL && ptr->item == 6);
  list.removeNode(ptr);
  printList(list);

  // now try removing from an empty list (should crash)
  cout << "The next check should crash the program." << endl;
  list.removeFront();
  printList(list);

  return 0;
}
