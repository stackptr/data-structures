/* wordweights.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Defines the WordWeights class interface.
 */

#ifndef WORDWEIGHTS_H
#define WORDWEIGHTS_H

#include <iostream>
#include <string>
#include <map> // TODO: Use unordered_map instead

class WordWeights {
public:
  WordWeights():num_words(0){};
  void Add(const std::string&);
  double WordFreq(const std::string&) const;
  void Print() const;

private:
  std::map<std::string, unsigned int> words;
  unsigned int num_words;


};
#endif