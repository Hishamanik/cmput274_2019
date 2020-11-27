#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <cassert>

using namespace std;

/*
  Practice problems:
    - Implement insertBack().

    - Implement insertAfter(), which is like insertBefore() except the item
      should appear after the one you insert.

      HINT: Do you really need to juggle pointers yourself or can you do it using
      the functions that already exist?

    - Implement a method remove(const T& item) that will remove the first
      occurrence of the item in the list.

    - Implement a method removeAll(const T& item) that will remove all
      occurrences of the item in the list in O(n) time
      where n is the number of items currently in the list. That is,
      don't restart the search for the item after removing the first occurrence.
*/


/*
  Struct for holding an item and pointers to the next and previous node
    in the linked list.

  NOTE: For an even more advanced practice, modify our structure so
    the user cannot modify the *next and *prev pointers directly.
    Perhaps add functions to return the next and prev pointers so the user
    can use them to crawl along the list, but the next and prev pointers
    should be private (maybe turn this into a class then because there is
    a lot of functionality if you do this).

    You might have to research "friend" classes to give LinkedList
    access to ListNode's private variables.
*/
template <typename T>
struct ListNode {
  // constructor
  ListNode(const T& item, ListNode<T> *prev = NULL, ListNode<T> *next = NULL) {
    this->item = item;
    this->prev = prev;
    this->next = next;
  }

  T item;
  ListNode<T> *next, *prev;
};


// A linked list, just as discussed in the slides.
template <typename T>
class LinkedList {
public:
  // create an empty linked list
  LinkedList();

  // will free each node from memory before terminating
  ~LinkedList();

  // insert an item into the back of the list
  void insertFront(const T& item);

  // remove the item at the front of the list
  void removeFront();

  // remove the item at the back of the list
  void removeBack();

  // assumes the node is in this list
  // will insert the item just before this node in the list
  void insertBefore(const T& item, ListNode<T> *node);

  // assumes the node is in this list
  void removeNode(ListNode<T> *node);

  // returns the number of items in the list
  unsigned int size() const;

  // Get ListNode pointers to the first and last items in the list,
  // respectively. Both return a pointer to NULL if the list is empty.
  ListNode<T>* getFirst() const;
  ListNode<T>* getLast() const;

  // Find and return a pointer to the first node holding the item.
  // Returns the NULL pointer if the item is not in the list.
  ListNode<T>* find(const T& item) const;

private:
  ListNode<T> *first, *last;
  unsigned int listSize;
};


template <typename T>
LinkedList<T>::LinkedList() {
 first = last = NULL;
 listSize = 0;
}


template <typename T>
LinkedList<T>::~LinkedList() {
  // delete one item at a time until the list is empty
  while (size() > 0) {
    removeFront();
  }
}


template <typename T>
void LinkedList<T>::insertFront(const T& item) {
  // get a new ListNode to hold the item
  // it points back to NULL and ahead to the first node in current list
  ListNode<T> *node = new ListNode<T>(item, NULL, first);

  // if the list is not empty, have the first node point back to the new node.
  if (first != NULL) {
    first->prev = node;
  }
  else {
    // otherwise, this new node is also the last node
    last = node;
  }

  // update the first node
  first = node;
  listSize++;
}



template <typename T>
void LinkedList<T>::insertBefore(const T& item, ListNode<T> *link) {
  // if the link is the start of the list, just call insertFront
  if (link == first) {
    insertFront(item);
    return;
  }

  // get a new node to hold this item
  ListNode<T> *node = new ListNode<T>(item, link->prev, link);

  // redirect surrounding links, the order you do this is important!
  link->prev->next = node;
  link->prev = node;
  listSize++;
}


template <typename T>
void LinkedList<T>::removeFront() {
  assert(first != NULL);

  ListNode<T> *toDelete = first;

  // if this is not the only item in the list, redirect
  // the prev pointer of the 2nd item to NULL
  if (first != last) {
    first->next->prev = NULL;
  }
  else {
    // otherwise, the list will become empty
    last = NULL;
  }

  // this works even if the list had size 1
  first = first->next;

  delete toDelete;
  listSize--;
}


template <typename T>
void LinkedList<T>::removeBack() {
  assert(first != NULL);

  ListNode<T> *toDelete = last;

  // if this is not the only item in the list, redirect
  // the next pointer of the 2nd last item to NULL
  if (first != last) {
    last->prev->next = NULL;
  }
  else {
    // otherwise, the list will become empty
    first = NULL;
  }

  // this works even if the list had size 1
  last = last->prev;

  delete toDelete;
  listSize--;
}


template <typename T>
void LinkedList<T>::removeNode(ListNode<T>* node) {
  // if we are removing the first or the last item, call that function
  if (node == first) {
    removeFront();
  }
  else if (node == last) {
    removeBack();
    return; // nothing followed the last node
  }
  else {
    // bypass the node we are deleting by redirecting pointers of surrounding nodes
    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
    listSize--;
  }
}


template <typename T>
unsigned int LinkedList<T>::size() const {
  return listSize;
}


template <typename T>
ListNode<T>* LinkedList<T>::getFirst() const {
  return first;
}


template <typename T>
ListNode<T>* LinkedList<T>::getLast() const {
  return last;
}


template <typename T>
ListNode<T>* LinkedList<T>::find(const T& item) const {
  // crawl along the list until the item is found
  ListNode<T>* node = first;
  while (node != NULL && node->item != item) {
    node = node->next;
  }

  // returns NULL if the item was not found
  return node;
}

#endif
