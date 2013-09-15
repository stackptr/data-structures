#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>

class word {
    public:
    word():w(""), freq(0) {}
    word(std::string arg1):w(arg1), freq(1) {}
    word(std::string arg1, int arg2):w(arg1), freq(arg2) {}
    friend const bool operator== (const word&, const word&);
    friend const bool operator!= (const word&, const word&);
    friend const bool operator< (const word&, const word&);
    friend const bool operator> (const word&, const word&);
    friend std::ostream& operator<< (std::ostream&, const word&);
    void updateFreq() { freq++; }

    std::string w;
    unsigned int freq;
};

#endif
