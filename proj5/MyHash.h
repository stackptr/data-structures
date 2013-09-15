/* MyHash.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Implements a hash function that maps a string to an integer
 */

#ifndef MYHASH_H
#define MYHASH_H

#include <string>


class MyHash {
public:
  size_t operator()(const std::string & key) const {
    int hashVal = 0;

    for (unsigned int i = 0; i < key.length(); i++)
      hashVal = 37 * hashVal + key[i];
    return hashVal;
  }
};

#endif