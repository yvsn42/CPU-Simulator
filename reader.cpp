#include "reader.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

istream& operator>>(istream &inf, Reader &reader)
{
  char *buffer = new char[sizeof(inf)]; // Line of assembly code
  char *b; // Char pointer to buffer
  int i, j;
  
  for(i = 0, j = 100; inf.getline(buffer, sizeof(inf)); )
  {
    b = buffer;
    
    while(*b)
    {
      if(*b == '\t')
        *b = ' ';
      b++;
    }// while *b
 
    while(isspace(*buffer))
      buffer++;

    if(*buffer == '.' || strstr(buffer, "main:") || *buffer == '_')
    //Check for directives(that start with '.')
      continue;

    //Allocate modified line to the "Instruction2" dynamically here
    reader.lines[i].setInfo(buffer);
    reader.lines[i].setAddress(j);
    i++;
    j += 4;
  }// for i

  return inf;
}// operator>> ()

void Reader::fetch(Instruction2 *x, Registers *r)const
{
  int i;  
  
  for(i = 0; i <= 1000; i++)
  {
    if(lines[i].getAddress() == r->get(Registers::eip))
    //find the Instruction matching the address in eip
    {
      x->setInfo(lines[i].getInfo());
      r->set(Registers::eip, r->get(Registers::eip) + 4);
      break;
    }// if lines[i].getAddress()
  }// for i

}// fetch ()
