#include "labels.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

istream& operator>>(istream &inf, Labels &labels)
{
  char *buffer = new char[sizeof(inf)]; // Line of assembly code
  //char *c; // Char pointer for ':'
  int i, j;
  labels.count = 0;
  
  for(i = 0, j = 100; inf.getline(buffer, sizeof(inf)); )
  {
    while(isspace(*buffer))
      buffer++;
    
    if(buffer[strlen(buffer) - 1] != ':')
    {  
    
      if(*buffer != '_' && *buffer != '.' && i != 0)
          labels.count += 4;
       continue;
    }// if buffer
    
    buffer[strlen(buffer) - 1] = '\0'; // Termianate string at ':'(For Labels)
    //Allocate modified line to the "Instruction2" dynamically here
    labels.l[i].setInfo(buffer);

    if(labels.count != 0)
      j += labels.count;

    labels.l[i].setAddress(j);
    labels.count = 0;
    i++;
   }// for i
  return inf;
}// operator>> ()

int Labels::find(const char *str)const
{
  for(int i = 0; i < 100; i++)
  {

    if(strcmp(str, l[i].getInfo()) == 0)
      return l[i].getAddress();
  } // for i

  return 0;
}// find()
