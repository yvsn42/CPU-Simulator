#include "registers.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

int Registers::get(Registers::RegName e)const
{
  switch(e)
  {
    case eax:
    case ebp:
    case esp:
    case eip:
    case edx:
    case ebx:
    case ecx:
    case flags: return regs[e];
                break;
    default: return 0;
  } // switch(e)
} // get()

void Registers::set(Registers::RegName e, int n)
{
  switch(e)
  {
    case eax:
    case ebp:
    case esp:
    case eip:
    case edx:
    case ebx:
    case ecx:
    case flags: regs[e] = n;
                break;
    default: return;
  } // switch(e)
} // set()

void Registers::setFlags(int x)
{
  //setSF
  if(x == 0)
    regs[flags] = regs[flags] | 64;
  else // If the result is non-zero
  {
    regs[flags] = regs[flags] & ~64;
    
    if(x < 0) // If the result is negative
      regs[flags] = regs[flags] | 128;
    else // If the result is positive
      regs[flags] = regs[flags] & ~128;
  }// else
}//setFlags()

bool Registers::getSF()const
{
return regs[flags] & 64;
}//getSF()

bool Registers::getZF()const
{
return regs[flags] & 128;
}//getZF()

int Registers::operator+=(int x)// Only for esp
{ 
  regs[esp] += x;
  return regs[esp];
}// += operator

Registers::Registers()
{
  regs[esp] = 1000;
  regs[ebp] = 996;
  regs[eip] = 100;
  regs[eax] = 0;
  regs[edx] = 0;
  regs[ebx] = 0;
  regs[ecx] = 0;
  regs[flags] = 0xC0;
}// Registers () [Default constructor]

int* Registers::address(char *operand, Memory &memory, const Labels &labels)
{
  static int value;
  char *e;
  int c = 0;

  if(operand == NULL)
    return NULL;

  if(operand[0] == '$') // immediate mode
  {
    value = atoi(&operand[1]);
    return &value;
  } // if immediate mode

  for(e = operand; *e ; e++)
    if(*e == '%')
      c++;
  
  if(c == 1)
    return indirAddress(operand, memory);
  
  else // ScaledIndex addressing
  if(c == 2) 
    return scAddress(operand, memory);

  else // Labels
  {
    value = labels.find(operand);
    return &value;
  } // else

  return 0;
} // address ()

int* Registers::indirAddress(char *operand, Memory &memory)
{
  int regNum, index;
  char regNames[8][7] = 
  {
    "eax", "ebp", "esp", "eip", "edx", "ebx", "ecx", "flags"
  }; // regNames
  char *ptr;

  for(regNum = eax; regNum <= flags; regNum++)
    if(strstr(operand, regNames[regNum]))
      break;

  ptr = strchr(operand, '(');

  if(ptr) // some form of indirect addressing
  {
    *ptr = '\0';  // terminate operand string at first '('
    index = atoi(operand);  // will return 0 if no number there!
    Data &data = dynamic_cast <Data&>(memory[regs[regNum] + index]);
    return  &data.get();
  } // if ptr

  else  // direct addressing
    return &(regs[regNum]);
}// indirAddress ()

int* Registers::scAddress(char *operand, Memory &memory)
{
  int regNum1, regNum2, index, size;
  char regNames[8][7] = 
  {
    "eax", "ebp", "esp", "eip", "edx", "ebx", "ecx", "flags"
  }; // regNames
  char *ptr; 
  
  ptr = strchr(operand, ',');
  
  for(regNum2 = eax; regNum2 <= flags; regNum2++)
    if(strstr(++ptr, regNames[regNum2]))
      break;
 
   for(regNum1 = eax; regNum1 <= flags; regNum1++)
     if(strstr(operand, regNames[regNum1]) && regNum2 != regNum1)
       break;
 
  ptr = strchr(operand, ')');
  *ptr = '\0'; // terminate operand string at first ')'

  ptr = strrchr(operand, ',');
  size = atoi(++ptr);
  ptr = strchr(operand, '(');
  *ptr = '\0';
  index = atoi(operand);  // will return 0 if no number there!
  int temp = (regs[regNum1] + (regs[regNum2] * size)) + index;
  Data &data = dynamic_cast <Data&>(memory[temp]);
  return  &data.get();
}// scAddress ()

ostream& operator<<(ostream& out, const Registers &r)
{
  out << "eip:" << setw(4) << right << r.regs[Registers::eip] << " ";
  out << "eax:" << setw(4) << r.regs[Registers::eax] << " ";
  out << "ebp:" << setw(4) << r.regs[Registers::ebp] << " ";
  out << "esp: " << r.regs[Registers::esp] << " ";
  out << "edx:" << setw(4) << r.regs[Registers::edx] << " ";
  out << "ebx:" << setw(4) << r.regs[Registers::ebx] << " ";
  out << "ecx:" << setw(5) << r.regs[Registers::ecx] << " ";
  out << "flags:" << setw(4) << r.regs[Registers::flags];
  return out;
}// operator<<()
