#include "memory.h"
#include "registers.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

ListNode::ListNode(Word *w, ListNode *l):word(w), next(l){};

ListNode::~ListNode()
{
  if(word)
    delete word;
} // ~ListNode()

Memory::Memory():head(NULL){};

Memory::~Memory()
{
  ListNode *ptr;
  
  for(ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } //for ptr
} //~Memory()

Word& Memory::operator[](int a)
{
  Word *A = new Word(a);
  ListNode *ptr;

  for(ptr = head; ptr; ptr = ptr->next)
  {
    if(!(*ptr->word < *A) && !(*A < *ptr->word))
      return *ptr->word;
  } // for ptr
  
  Data *d = new Data(a);
  insert(d);
  return *d;
} // [] operator

const Word& Memory::operator[](int a)const
{
  Word *A = new Word(a);
  ListNode *ptr;

  for(ptr = head; ptr; ptr = ptr->next)
  {
    if(!(*ptr->word < *A) && !(*A < *ptr->word))
      return *ptr->word;
  } // for ptr
  
  cout << "Seg fault at address: " << a << endl;
  exit(1);
} // [] operator

void Memory::insert(Word *ins)
{
  ListNode *ptr, *prev = NULL;
  ptr = head;

  for(ptr = head; ptr && *ptr->word < *ins; prev = ptr, ptr = ptr->next);
  
  if(prev) // if list not empty
    prev -> next = new ListNode(ins, ptr);
  else // if list is empty
    head = new ListNode(ins, head);
} // insert()

istream& operator>>(istream &inf, Memory &memory)
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

    if(*buffer == '.' || buffer[strlen(buffer) - 1] == ':' || *buffer == '_')
    //Check for directives(that start with '.')
      continue;

    //Allocate modified line to the "Instruction" dynamically here
    Instruction *in = new Instruction(j);
    *in = buffer;
    memory.insert(in); 
    i++;
    j += 4;
  }// for i

  return inf;
}// operator>> ()

const Instruction& Memory::fetch(Registers *r)const
{
  int i = r->get(Registers::eip);
  const Instruction &x = dynamic_cast <const Instruction&>((*this)[i]);
  //find the Instruction matching the address in eip
  r->set(Registers::eip, r->get(Registers::eip) + 4);
  return x;
}// fetch ()
