#ifndef MEMORY_H
#define MEMORY_H

#include "word.h"

// Forward declare Registers and Memory classes
class Registers;
class Memory;

class ListNode
{
  Word *word;
  ListNode *next;

  ListNode(Word *w, ListNode *l);
  ~ListNode();
  friend Memory;
}; // class ListNode

class Memory 
{
  ListNode *head;

public:
  Word& operator[](int a);
  const Word& operator[](int a)const;
  Memory();
  ~Memory();
  void insert(Word* ins);
  friend istream& operator>>(istream &inf, Memory &memory);
  const Instruction& fetch(Registers *r)const;
}; // class Memory

#endif
