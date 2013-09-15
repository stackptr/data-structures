#include <cstddef>
#include <iostream>

#ifndef DLL_H
#define DLL_H

template<typename T>
class DLL {
private:
  struct Node{
    T data;
    Node *prev, *next;

    Node(const T& d = T(), Node *p = NULL, Node *n = NULL)
    : data(d), prev(p), next(n){}
  };

public:
//*****************************************************
// Iterators
//*****************************************************
  class const_iterator {
    public:
      const_iterator() : current(NULL){}
      const T& operator*() const {
        return retrieve();
      }
      const_iterator& operator++(){
        current = current->next;
        return *this;
      }
      const_iterator& operator--(){
        current = current->prev;
        return *this;
      }
      
      const_iterator operator++(int){
        const_iterator result = *this;
        ++(*this);
        return result;
      }
      const_iterator operator--(int){
        const_iterator result = *this;
        --(*this);
        return result;
      }


      bool operator== (const const_iterator& rhs) const
        {return current == rhs.current; }
      bool operator!= (const const_iterator& rhs) const
        {return !(*this == rhs);}

    protected:
      Node *current;
      T& retrieve() const { return current->data;}
      const_iterator(Node *p): current(p) {}

      friend class DLL<T>;
  };
  
  class iterator : public const_iterator {
    public:
      iterator(){}

      T& operator*() { return retrieve();}
      const T& operator* () const { return const_iterator::operator*();}
      
      iterator& operator++(){
        const_iterator::current = current->next;
        return *this;
      }
      
      iterator& operator--(){
        const_iterator::current = current->prev;
        return *this;
      }

      iterator operator++(int){
        iterator result = *this;
        ++(*this);
        return result;
      }

      iterator operator--(int){
        iterator result = *this;
        --(*this);
        return result;
      }

    protected:
      using const_iterator::current;
      using const_iterator::retrieve;
      iterator(Node *p): const_iterator(p){}
      friend class DLL<T>;
  };

//*****************************************************
// Constructor, destructor, copy, and operator= overload
//*****************************************************
  DLL(){init();}
  DLL(const DLL& rhs){ init(); *this = rhs; }
  ~DLL(){
    clear();
    delete head;
    delete tail;
  }

  const DLL& operator= (const DLL& rhs){
    if (this == &rhs)
      return *this;
    clear();
    for(const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
      push_back(*itr);
    return *this;
  }

//*****************************************************
// Definitions of the list
//*****************************************************
  int size() const { return theSize; }
  bool empty() const { return size() == 0;}

//*****************************************************
// Iterator return types
//*****************************************************
  iterator begin(){ return iterator(head->next); }
  const_iterator begin() const { return const_iterator(head->next); }
  iterator end() { return iterator( tail); }
  const_iterator end() const { return const_iterator(tail); }

//*****************************************************
// List accessors
//*****************************************************
  T& front(){ return *begin();}
  const T& front() const { return *begin();}
  T& back() { return *--end(); }
  const T& back() const { return *--end(); }

//*****************************************************
// List mutators
//*****************************************************

  void push_front(const T& x){ insert(begin(), x); }
  void push_back(const T& x){ insert(end(), x); }
  void pop_front() { erase(begin() );}
  void pop_back() { erase(--end() ); }

  iterator insert(iterator itr, const T& x){
    Node *p = itr.current;
    theSize++;
    return iterator(p->prev = p->prev->next = new Node(x, p->prev, p) );
  }

  iterator erase(iterator itr){
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
  }

  iterator erase(iterator start, iterator end){
    for(iterator itr = start; itr != end; )
      itr = erase(itr);
    return end;
  }
  
  void clear(){
    while(!empty() )
      pop_front();
  }

//*****************************************************
// Assignment specific functions
//*****************************************************

  // Searches for data and returns an iterator pointing to the found Node or
  // to the end if no Node contains the data.
  iterator find(const T& x) {
    for(iterator itr = begin(); itr != end(); itr++){
      if( *itr == x){
        return itr;
      }
    }
    return end();
  }

  iterator findAndMove(const T& x) {
    for(iterator itr = begin(); itr != end(); itr++){
      if( *itr == x){
        moveUp(itr);
        moveUp(itr);
        return itr;
      }
    }
    return end();
  }

  // Given an iterator, shifts the node at the iterator toward the front of the list
  // by one position.
  void moveUp(iterator itr){
    if(head->next == itr.current)
      return;
    else{
      Node *p = itr.current;
      Node *p1 = p->prev;
      Node *n = p->next;
      p1->prev->next = p;
      p->prev = p1->prev;
      p->next = p1;
      p1->prev = p;
      p1->next = n;
      n->prev = p1;
    }
  }

private:
  int theSize;
  Node *head, *tail;

  void init(){
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
  }

};
#endif
