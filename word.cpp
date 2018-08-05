#include "word.h"

Word::Word(int a):address(a)
{
} // Word()

Word::~Word()
{
} // ~Word()

bool Word::operator<(const Word rhs)const
{
return address < rhs.address;
}// < operator
