#include <iostream>
#include "linked_list.h"

using namespace std;


// Function to print the entire contents of a linked list (and the list size).
void checkAndPrint(LinkedList<int>& list) {
  cout << "List size: " << list.size() << endl;
  cout << "Contents:";

  for (ListNode<int> *node = list.getFirst(); node != NULL; node = node->next) {
    cout << ' ' << node->item;
  }

  cout << endl << endl;
}

int main() {
  LinkedList<int> list;

  // insert these items into the list using insertFront,
  // so the resulting list is in reverse order
  int insertList[] = {1, 1, 5, 3, 1, 7, 14, 6, 5};
  for (int i = 0; i < 9; i++) {
    list.insertFront(insertList[i]);
  }

  // print the list
  checkAndPrint(list);

  // check that 8 is not in the list
  ListNode<int> *ptr = list.find(8);
  assert(ptr == NULL);

  // check that 5 is in the list
  ptr = list.find(5);
  assert(ptr != NULL && ptr->item == 5);

  // check removing a link
  list.removeNode(ptr);
  checkAndPrint(list);

  // there should be another copy of 5, so check that it is in the list
  // and remove it
  ptr = list.find(5);
  assert(ptr != NULL && ptr->item == 5);
  list.removeNode(ptr);
  checkAndPrint(list);

  // should have removed all 5s by now
  assert(list.find(5) == NULL);

  // insert 17 just before the 14
  ptr = list.find(14);
  assert(ptr != NULL);
  list.insertBefore(17, ptr);
  checkAndPrint(list);

  // now pop all but one item from the list, leaving only the first item
  while (list.size() > 1) {
    list.removeBack();
  }
  checkAndPrint(list);

  // make sure it was the 3 that we left and remove it
  ptr = list.find(6);
  assert(ptr != NULL && ptr->item == 6);
  list.removeNode(ptr);
  checkAndPrint(list);

  // now try removing from an empty list (should crash)
  cout << "The next check should crash the program." << endl;
  list.removeFront();
  checkAndPrint(list);

  return 0;
}
