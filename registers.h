#ifndef REGISTERS_H
#define REGISTERS_H

#include "labels.h"
#include "memory.h"
#include "data.h"
#include <iostream>
using namespace std;

class Registers
{
  int regs[8];

  int *indirAddress(char *operand, Memory &memory);
  int *scAddress(char *operand, Memory &memory);

public:
  typedef enum {eax, ebp, esp, eip, edx, ebx, ecx, flags}RegName;

  Registers();
  int get(Registers::RegName e)const;
  void set(Registers::RegName e, int n);
  void setFlags(int x);
  bool getSF()const;
  bool getZF()const;
  int operator+=(int x);
  int* address(char *operand, Memory &memory, const Labels &labels);
  friend ostream& operator<<(ostream& out, const Registers &r);
}; //class Registers
#endif
