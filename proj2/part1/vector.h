/* vector.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Implementation for a generic Vector class. Functions list:
 *  void resize(n) - Changes size of Vector
 *  void increase(n) - Reserves more memory for Vector
 *  void push_back(&e) - Adds elements to end of Vector
 *  void pop_back()
 *  const T& back() - Returns last element of Vector
 *  T& operator[](n) - Accesses nth value in Vector
 *  int size() - Returns size of Vector
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

#define INIT_SIZE 5

template <typename T>
class Vector{
public:

// Constructor
Vector():v_size(0), capacity(INIT_SIZE) {data = new T[INIT_SIZE];}

// Destructor: free dynamic memory
~Vector(){
  delete [] data;
}

// resize: Changes size of Vector
void resize(int newSize){
  if(newSize > capacity)
    increase(newSize * 2 + 1);
  v_size = newSize;
}

// increase: Reserves more memory for Vector
void increase(int newCapacity){
  if (newCapacity < v_size)
    return;
  
  T* temp = data;
  data = new T[newCapacity];
  for(int i = 0; i < v_size; i++)
    data[i] = temp[i];
  
  capacity = newCapacity;
  
  delete [] temp;


}

// push_back: Adds element to end of vector
void push_back(const T &e){
  if (v_size == capacity)
    increase(2 * capacity + 1);
  data[v_size++] = e;
}

// pop_back
void pop_back(){ v_size--;}

// back: Returns last element in Vector
const T& back() const{ return data[v_size - 1]; }

// Operator [] overload: Accesses nth element
T& operator[](const int n){
  assert(n >= 0 && n < v_size);
  return data[n];
}

// Returns size of Vector
int size(){return v_size;}

private:
  T *data;
  int v_size;
  int capacity;
};
#endif