#include "decoder.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

void Decoder::parse(const Instruction &x, Registers *r, 
                    Memory &m, const Labels &l)
{
  char *ptr;
  char p[strlen(x.getInfo())]; // Copy of the info in Information x 
  strcpy(p, x.getInfo());

  strcpy(opcode, strtok(p, " "));
  ptr = strtok(NULL, " ,");

  if(ptr)
  {
    operand1 = r->address(ptr, m, l);
    ptr = strtok(NULL, " ");

    if(ptr)
      operand2 = r->address(ptr, m, l);
  }// if ptr
}// decode ()

void Decoder::execute(Registers *r, const Instruction &x, Memory &mem)
{ 
  const char *opcodes[] = 
  { "addl", "andl", "leave", "movl", "pushl", "ret", "subl", "cmpl", "incl",
    "jg", "jle", "jmp", "leal", "call", "sall", "decl", "imull"
  }; //char opcodes
  enum OpcodeNum 
  {ADDL, ANDL, LEAVE, MOVL, PUSHL, RET, SUBL, CMPL, INCL,
   JG, JLE, JMP, LEAL, CALL, SALL, DECL, IMULL
  }; // enum OpcodeNum
  int opcodeNum;

  for(opcodeNum = ADDL;
    strcmp(opcode, opcodes[opcodeNum]) != 0 || opcodeNum > IMULL;
    ++opcodeNum);
  
  switch (opcodeNum)
  {
    case ADDL: addl(r); break;
    case ANDL: andl(r); break;
    case LEAVE: leave(r, mem); break;
    case MOVL: movl(); break;
    case PUSHL: pushl(r, mem); break;
    case RET: ret(r, mem); break;
    case SUBL: subl(r); break;
    case CMPL: cmpl(r); break;
    case INCL: incl(r); break;
    case JG: jg(r); break;
    case JLE: jle(r); break;
    case JMP: jmp(r); break;
    case LEAL: leal(x, r); break;
    case CALL: call(r, mem); break;
    case SALL: sall(r); break;
    case DECL: decl(r); break;
    case IMULL: imull(r); break;
    default: cout << "Invalid opcode!\n";
  } // switch on oncodeNum

} // execute()

void Decoder::addl(Registers *r)
{
  *operand2 += *operand1;
  r->setFlags(*operand2);
}// addl()

void Decoder::andl(Registers *r)
{
  *operand2 = *operand1 & *operand2;
  r->setFlags(*operand2);
}// andl()

void Decoder::subl(Registers *r)
{
  *operand2 -= *operand1;
  r->setFlags(*operand2);
}// subl()

void Decoder::imull(Registers *r)
{ 
  *operand2 *= *operand1;
  r->setFlags(*operand2);
}// imull()

void Decoder::cmpl(Registers *r)const
{
  r->setFlags(*operand2 - *operand1);
}// cmpl()

void Decoder::incl(Registers *r)
{
  r->setFlags(++*operand1);
}// incl()

void Decoder::decl(Registers *r)
{
  r->setFlags(--*operand1);
}// decl()

void Decoder::jg(Registers *r)const
{
  if(!r->getZF() && !r->getSF())
    r->set(Registers::eip, *operand1);
}// jg()

void Decoder::jle(Registers *r)const
{
  if(r->getZF() || r->getSF())
    r->set(Registers::eip, *operand1);
}// jle()

void Decoder::jmp(Registers *r)const
{
  r->set(Registers::eip, *operand1);
}//jmp()

void Decoder::leal(const Instruction &in, const Registers *r)
{
  char cpy[strlen(in.getInfo())]; // Copy of the info in Information x 
  strcpy(cpy, in.getInfo());
  strtok(cpy, " ");
  char *p = strtok(NULL, " ");
  Registers::RegName regNum = Registers::ecx;
  int i;
  char regNames[8][7] = 
  {
    "eax", "ebp", "esp", "eip", "edx", "ebx", "ecx", "flags"
  }; // regNames
  char *ptr;
  
  for(i = Registers::eax; i <= Registers::flags; i++)
    if(strstr(p, regNames[i]))
      break;

  switch(i)
  {
    case 0: regNum = Registers::eax; break;
    case 1: regNum = Registers::ebp; break;
    case 2: regNum = Registers::esp; break;
    case 3: regNum = Registers::eip; break;
    case 4: regNum = Registers::edx; break;
    case 5: regNum = Registers::ebx; break;
    case 6: regNum = Registers::ecx; break;
    case 7: regNum = Registers::flags; break;
  }// switch(i)

  ptr = strchr(p, '(');
  *ptr = '\0';  // terminate operand string at first '('
  // atoi() will return 0 if no number there!
  *operand2 = r->get(regNum) + atoi(p); 
}// leal()

void Decoder::movl()
{
  *operand2 = *operand1;
}// movl()

void Decoder::call(Registers *r, Memory &mem)const
{
  *r += -4;
  Data &data = dynamic_cast <Data&>(mem[r->get(Registers::esp)]);
  data = r->get(Registers::eip);
  r->set(Registers::eip, *operand1);
}// call()

void Decoder::sall(Registers *r)
{
  *operand2 = *operand2 << *operand1;
  r->setFlags(*operand2);
}// sall()

void Decoder::pushl(Registers *r, Memory &mem)const
{
  *r += -4;
  Data &data = dynamic_cast <Data&>(mem[r->get(Registers::esp)]);
  data = *operand1;
}// pushl()

void Decoder::leave(Registers *r, const Memory &mem)const
{
  r->set(Registers::esp, r->get(Registers::ebp));
  const Data &data = dynamic_cast <const Data&>(mem[r->get(Registers::esp)]);
  r->set(Registers::ebp, data.get());
  *r += 4;
}// leave()

void Decoder::ret(Registers *r, const Memory &mem)const
{
  const Data &data = dynamic_cast <const Data&>(mem[r->get(Registers::esp)]);
  r->set(Registers::eip, data.get());
  *r += 4;
}// ret()
