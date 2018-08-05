#include "instruction.h"
#include <iostream>
#include <cstring>
using namespace std;

Instruction::Instruction(int a): Word(a), info(NULL)
{
} // Instruction() [Constructor]

Instruction::~Instruction()
{
  if(info)
  delete [] info;
} // ~Instruction() [Destructor]

const char *Instruction::getInfo()const
{
  return info;
} // getInfo()

Instruction& Instruction::operator=(const char *c)
{
 
 if(c)
 {
   info = new char[strlen(c) - 1];
   strcpy(info, c);
 }// if (c)

 return *this;
} // setInfo()

ostream& operator<<(ostream &out, const Instruction &x)
{
  out << x.info;
  return out;
} // << operator
