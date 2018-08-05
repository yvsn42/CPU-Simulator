#ifndef READER_H
#define READER_H

#include "instruction2.h"
#include "registers.h"
#include <iostream>
using namespace std;

class Reader
{
  Instruction2 lines[1000];

public:
  friend istream& operator>>(istream &inf, Reader &reader);
  void fetch(Instruction2 *x, Registers *r)const;
}; //class Reader

#endif

