#include "word.h"
#include <iostream>

const bool operator== (const word &c1, const word &c2){ return c1.w == c2.w; }
const bool operator!= (const word &c1, const word &c2){ return c1.w != c2.w; }
const bool operator< (const word &c1, const word &c2){ return c1.w < c2.w; }
const bool operator> (const word &c1, const word &c2){ return c1.w > c2.w; }
std::ostream& operator<<(std::ostream &out, const word &c){
  return out << c.w;
}
