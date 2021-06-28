#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class List;
template <typename T>
class Iterator;

template <typename T>
class Node
{
public:
   /* 
      Constructs a node with a given data value.
      @param s the data to store in this node
   */
   Node(T s);
   ~Node();
   static int getCurCount() { return  curCount; } // new
   static void setCurCount(int n) { curCount = n; } // new

   static int getMaxCount() { return  maxCount; } // new
   static void setMaxCount(int n) { maxCount = n; } // New
private:
   T data;
   Node* previous;
   Node* next;
   static int curCount; // New
   static int maxCount; // New
friend class List<T>;
friend class Iterator<T>;
};

template <typename T>
class List
{
public:
   /**
      Constructs an empty list;
   */
   List();
   /**
      Appends an element to the list.
      @param s the value to append
   */
   List(const List<T>& right);
   ~List();
   List<T>& operator=(const List<T>& right);

   void push_back(T s);
   void push_front(T s);
   void insert(Iterator<T> iter, T s);
   Iterator<T> erase(Iterator<T> i);
   Iterator<T> begin() const;
   Iterator<T> end() const;

   bool empty() const;
   int size() const;
private:
   Node<T>* first;
   Node<T>* last;
};

template <typename T>
class Iterator
{
public:
   /**
      Constructs an iterator that does not point into any list.
   */
   Iterator();
   T get() const;
   void next();
   void previous();

   bool equals(Iterator<T> b) const;
   Iterator<T>& operator++(int);
   Iterator<T>& operator--(int);
   T operator*() const;
   T& operator*();
   T* operator->();
   bool operator==(const Iterator<T>& b) const;
   bool operator!=(const Iterator<T>& b) const;
private:
   Node<T>* position;
   Node<T>* last;
friend class List<T>;
};
// Template Class Implemention
template <typename T>
int Node<T>::curCount = 0;
template <typename T>
int Node<T>::maxCount = 0;

template <typename T>
Node<T>::Node(T s)
{
   data = s;
   previous = NULL;
   next = NULL;
	curCount++;
	maxCount = max(maxCount, curCount);
}
template <typename T>
Node<T>::~Node()
{
	curCount--;
}

template <typename T>
List<T>::List()
{
   first = NULL;
   last = NULL;
}
template <typename T>
List<T>::~List()
{
	if (!empty()) {
		Node<T>* p = first;
		while (p!=last) {
			Node<T>* nextp = p->next;
			delete p;
			p = nextp;
		}
		delete p;
	}
}
template <typename T>
List<T>::List(const List<T>& right){
	first = NULL;
	last = NULL;
	for (Iterator<T> iter=right.begin(); iter!=right.end(); iter++ ){
		push_back(*iter);
	}
}
template <typename T>
List<T>& List<T>::operator=(const List<T>& right){
	if (this != &right) {
		// Delete all Node
		if (!empty()) {
			Node<T>* p = first;
			while (p!=last) {
				Node<T>* nextp = p->next;
				delete p;
				p = nextp;
			}
			delete p;
		}
		// Copy right List
		first = NULL;
		last = NULL;
		for (Iterator<T> iter=right.begin(); iter!=right.end(); iter++ ){
			push_back(*iter);
		}
	}
	return *this;
}
template <typename T>
bool List<T>::empty() const
{
	return last == NULL;
}
template <typename T>
int List<T>::size() const
{
	int n = 0;
	for (Iterator<T> li = begin(); li!=end(); li++)
		n++;
	return n;
}

template <typename T>
void List<T>::push_back(T s)
{
   Node<T>* newnode = new Node<T>(s);
   if (last == NULL) /* list is empty */
   {
      first = newnode;
      last = newnode;
   }
   else
   {
      newnode->previous = last;
      last->next = newnode;
      last = newnode;
   }
}
template <typename T>
void List<T>::push_front(T s)
{
   Node<T>* newnode = new Node<T>(s);
   if (last == NULL) /* list is empty */
   {
      first = newnode;
      last = newnode;
   }
   else
   {
      newnode->next = first;
      first->previous = newnode;
      first = newnode;
   }
}

template <typename T>
void List<T>::insert(Iterator<T> iter, T s)
{
   if (iter.position == NULL)
   {
      push_back(s);
      return;
   }

   Node<T>* after = iter.position;
   Node<T>* before = after->previous;
   Node<T>* newnode = new Node<T>(s);
   newnode->previous = before;
   newnode->next = after;
   after->previous = newnode;
   if (before == NULL) /* insert at beginning */
      first = newnode;
   else
      before->next = newnode;
}

template <typename T>
Iterator<T> List<T>::erase(Iterator<T> i)
{
   Iterator<T> iter = i;
   assert(iter.position != NULL);
   Node<T>* remove = iter.position;
   Node<T>* before = remove->previous;
   Node<T>* after = remove->next;
   if (remove == first)
      first = after;
   else
      before->next = after;
   if (remove == last)
      last = before;
   else
      after->previous = before;
   iter.position = after;
   delete remove;
   return iter;
}

template <typename T>
Iterator<T> List<T>::begin() const
{
   Iterator<T> iter;
   iter.position = first;
   iter.last = last;
   return iter;
}

template <typename T>
Iterator<T> List<T>::end() const
{
   Iterator<T> iter;
   iter.position = NULL;
   iter.last = last;
   return iter;
}

template <typename T>
Iterator<T>::Iterator()
{
   position = NULL;
   last = NULL;
}

template <typename T>
T Iterator<T>::get() const
{
   assert(position != NULL);
   return position->data;
}

template <typename T>
void Iterator<T>::next()
{
   assert(position != NULL);
   position = position->next;
}

template <typename T>
void Iterator<T>::previous()
{
   if (position == NULL)
      position = last;
   else
      position = position->previous;
   assert(position != NULL);
}

template <typename T>
bool Iterator<T>::equals(Iterator<T> b) const
{
   return position == b.position;
}
template <typename T>
Iterator<T>& Iterator<T>::operator++(int)
{
   assert(position != NULL);
   position = position->next;
   return *this;
}
template <typename T>
Iterator<T>& Iterator<T>::operator--(int)
{
	if (position == NULL)
		position = last;
	else
		position = position->previous;
	assert(position != NULL);
	return *this;
}

template <typename T>
T Iterator<T>::operator*() const
{
   assert(position != NULL);
   return position->data;
}
template <typename T>
T& Iterator<T>::operator*()
{
   assert(position != NULL);
   return position->data;
}

template <typename T>
T* Iterator<T>::operator->()
{
	   assert(position != NULL);
	   return &(position->data);
}
template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& b) const
{
   return position == b.position;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& b) const
{
   return position != b.position;
}

#endif
