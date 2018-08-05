#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "word.h"
#include <iostream>
using namespace std;

class Instruction: public Word
{
  char *info;

public:
  Instruction(int a);
  ~Instruction();
  const char* getInfo()const;
  Instruction& operator=(const char* c);
  friend ostream& operator<<(ostream& out, const Instruction &x);
}; // class Instruction
#endif
