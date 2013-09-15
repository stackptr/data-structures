/* wordlist.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Defines the WordList class.
 */

#include <string>
#include "dll.h"

#ifndef WORDLIST_H
#define WORDLIST_H

class word {
    public:
    word():w(""), freq(0) {}
    word(std::string arg1):w(arg1), freq(1) {}
    word(std::string arg1, int arg2):w(arg1), freq(arg2) {}
    bool operator== (const word &c){ return w == c.w; }
    bool operator!= (const word &c){ return !(w == c.w); }
    void updateFreq() { freq++; }

    std::string w;
    unsigned int freq;
};

class WordList {
public:
  WordList():num_words(0){}
  void Add(const std::string&);
  double WordFreq(const std::string&);
  void Print(unsigned int);

private:
  DLL<word> wlist;
  unsigned int num_words;

};
#endif
