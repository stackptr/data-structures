/* driver.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Driver program to test Vector and Stack classes
 */

#include <iostream>
#include <string>
#include "vector.h"
#include "stack.h"

int main(){
  // Create a Vector
  Vector<int> v;
  
  // Push some data
  v.push_back(3);
  v.push_back(9);
  v.push_back(-7);
  v.push_back(8.3);
  v.push_back(100000);

  // Print data back:
  for(int i = 0; i < v.size(); i++)
    std::cout << "v[" << i << "]: " << v[i] << std::endl;

  // Create a Stack
  double test = 4.3;
  Stack<double> s;
  s.push(9.3);
  s.push(7.8);
  s.push(test);
  std::cout << "Top of stack: " << s.top() << std::endl;
  
  s.pop();
  
  std::cout << "Top of stack: " << s.top() << std::endl;
  
  s.top() -= 4;

  std::cout << "Top of stack: " << s.top() << std::endl;
}