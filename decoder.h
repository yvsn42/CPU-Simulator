#ifndef DECODER_H
#define DECODER_H

#include "registers.h"
#include "memory.h"
#include "data.h"

class Decoder
{
  char opcode[20];
  int *operand1;
  int *operand2;
  
  void addl(Registers *r);
  void andl(Registers *r);
  void leave(Registers *r, const Memory& mem)const;
  void movl();
  void pushl(Registers *r, Memory& mem)const;
  void ret(Registers *r, const Memory& mem)const;
  void subl(Registers *r);
  void cmpl(Registers *r)const;
  void incl(Registers *r);
  void jg(Registers *r)const;
  void jle(Registers *r)const;
  void jmp(Registers *r)const;
  void leal(const Instruction &in, const Registers *r);
  void call(Registers *r, Memory& mem)const;
  void sall(Registers *r);
  void decl(Registers *r);
  void imull(Registers *r);

public:
  void parse(const Instruction &x, Registers *r, 
             Memory& mem, const Labels &lab);
  void execute(Registers *r, const Instruction &x, Memory& mem);
}; // class Decoder
#endif
