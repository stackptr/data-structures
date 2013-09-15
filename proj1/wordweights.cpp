/* wordweights.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Implements WordWeights class.
 */

#include <iostream>
#include "wordweights.h"

/* Add
 *
 * Given a string, checks to see if the string exists in the map. If it
 * does, the value associated with the word is incremented by 1. If not,
 * word is added with a value of 1.
 */
void WordWeights::Add(const std::string &w){
  if (w == "") // For some reason, empty strings are sometimes read as words
    return;
  words[w]++;
  num_words++;
}

/* WordFreq
 *
 * Given a string, returns the frequency of the word in the map.
 */
double WordWeights::WordFreq(const std::string &w) const {
  std::map<std::string, unsigned int>::const_iterator it = words.find(w);
  if ( it == words.end())
    return 0;
  return (double) it->second / num_words;

}

/* Print
 *
 * Prints the words and associated frequency. Useful for making sure files are
 * being read in correctly.
 */
void WordWeights::Print() const {
  std::cout << "Print words map:\n";
  std::map<std::string, unsigned int>::const_iterator it;
  for ( it=words.begin(); it != words.end(); it++)
    std::cout << it->first << " => " << (double) it->second/num_words << std::endl;
  std::cout << "Word count: " << num_words << std::endl;
}