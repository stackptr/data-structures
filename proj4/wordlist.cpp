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
  if (!wlist.contains(word(w)) )
    wlist.insert(word(w)); // Doesn't exist, so insert the word into the tree
  else
    wlist.get(word(w)).updateFreq();
  num_words++;
}

/* WordFreq
 *
 * Given a string, returns the frequency of the word in the map.
 * For each word found in the list, the word is moved two steps up
 * in the tree using rotations.
 */
double WordList::WordFreq(const std::string &w) {
  if (!wlist.contains(word(w)) )
    return 0;
  return (double) wlist.getAndUpdate(word(w)).freq/num_words;
}

/* Print
 *
 * Prints the first n words in the word list.
 */
void WordList::Print(unsigned int n) {
  //wlist.printTree();
  wlist.printPreorder(n);
}
