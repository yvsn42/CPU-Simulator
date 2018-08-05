#ifndef LABELS_H
#define LABELS_H

#include "instruction2.h"
#include <iostream>
using namespace std;

class Labels
{
  Instruction2 l[100];
  int count;

public:
  friend istream& operator>>(istream& inf, Labels &labels);
  int find(const char *str)const;
}; //class Labels

#endif
