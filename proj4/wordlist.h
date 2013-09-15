/* wordlist.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Defines the WordList class.
 */

#include <iostream>
#include <string>
#include "bst.h"
#include "word.h"

#ifndef WORDLIST_H
#define WORDLIST_H

class WordList {
public:
  WordList():num_words(0){}
  void Add(const std::string&);
  double WordFreq(const std::string&);
  void Print(unsigned int);

private:
  BST<word> wlist;
  unsigned int num_words;

};
#endif
