#ifndef DATA_H
#define DATA_H

#include "word.h"

class Data: public Word
{
  int num;

public:
  Data(int aa);
  int& get();
  const int& get()const;
  int& operator=(int rhs);
}; // class Data (derived from Word)

#endif
