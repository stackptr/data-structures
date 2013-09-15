/* stack.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Uses the Vector class for an implementation of a Stack.
 */

#ifndef STACK_H
#define STACK_H

#include "vector.h"

template <typename T>
class Stack{
public:
  Stack(){}
  ~Stack(){}
  void push(const T& e){data.push_back(e);}
  void pop(){data.pop_back();}
  T& top(){return data[data.size()-1];}
  bool empty(){return data.size();}
private:
  Vector<T> data;
};
#endif