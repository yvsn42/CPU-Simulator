#include "data.h"

Data::Data(int aa):Word(aa)
{
} // Data()

int& Data::get()
{
  return num;
} // get()

const int& Data::get()const
{
  return num;
} // get() const

int& Data::operator=(int rhs)
{
  num = rhs;
  return num;
} // = operator
