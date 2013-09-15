/* wordlist.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Implements the WordList class.
 */

#include <iostream>
#include "wordlist.h"

/* Adds a word to the end of the list if it doesn't exist, or updates the
 * frequency of that word if it already exists.
 */
void WordList::Add(const std::string &w){
  if (w == "") // For some reason, empty strings are sometimes read as words
    return;
  
  // Check to see if the word already exists
  DLL<word>::iterator pos = wlist.find(w);
  if ( pos == wlist.end())
    wlist.push_back(word(w) ); // Doesn't exist, push the word to the end
  else
    (*pos).updateFreq(); // Already exists, update the frequency counter
  num_words++;
}

/* WordFreq
 *
 * Given a string, returns the frequency of the word in the map.
 */
double WordList::WordFreq(const std::string &w) {
  DLL<word>::iterator itr = wlist.findAndMove(w);
  if ( itr == wlist.end())
    return 0;
  return (double) (*itr).freq / num_words;
}

/* Print
 *
 * Prints the first n words in the word list.
 */
void WordList::Print(unsigned int n) {
  DLL<word>::const_iterator itr = wlist.begin();
  while( itr != wlist.end() && n != 0){
    std::cout << (*itr).w << "\t\t" << (double) (*itr).freq/num_words << std::endl;
    n--;
    itr++;
  }
  std::cout << "Word count: " << num_words << std::endl;
}