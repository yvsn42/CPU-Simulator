#include "instruction2.h"
#include <iostream>
#include <cstring>
using namespace std;

Instruction2::Instruction2()
{
  info = NULL;
} // Instruction() [Constructor]

Instruction2::~Instruction2()
{
  if(info)
  delete [] info;
} // ~Instruction2() [Destructor]

const char *Instruction2::getInfo()const
{
  return info;
} // getInfo()

int Instruction2::getAddress()const
{
  return address;
} // getAddress()

void Instruction2::setInfo(const char *c)
{
 
 if(c)
 {
   info = new char[strlen(c) - 1];
   strcpy(info, c);
 } // if (c)
} // setInfo()

void Instruction2::setAddress(int a)
{
  address = a;
} // setAddress()
