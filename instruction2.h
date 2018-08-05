#ifndef INSTRUCTION2_H
#define INSTRUCTION2_H

class Instruction2
{
  int address;
  char *info;

public:
  Instruction2();
  ~Instruction2();
  const char* getInfo()const;
  int getAddress()const;
  void setInfo(const char *c);
  void setAddress(int a);
}; // class Instruction2
#endif
