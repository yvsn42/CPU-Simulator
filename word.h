#ifndef WORD_H
#define WORD_H

class Word
{
  int address;

public:
  Word(int a);
  virtual ~Word();
  bool operator<(const Word rhs)const;
}; // class Word

#include "data.h"
#include "instruction.h"
#endif
