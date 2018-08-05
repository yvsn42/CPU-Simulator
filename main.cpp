// MAIN.C FILE
#include "registers.h"
#include "instruction.h"
#include "instruction2.h"
#include "memory.h"
#include "word.h"
#include "data.h"
#include "labels.h"
#include "decoder.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
  Decoder decoder;
  Registers registers;
  Labels labels;
  Memory memory;  
  Data *d1 = new Data(1000);
  *d1 = 0;
  memory.insert(d1);
  Data *d2 = new Data(992);
  *d2 = 0;
  memory.insert(d2);
  ifstream inf(argv[1]);
  inf >> memory;
  inf.clear();
  inf.seekg(0);
  inf >> labels;
  registers.set(Registers::eip, labels.find("main"));
 
  while(registers.get(Registers::eip))
  { 
    const Instruction &x = memory.fetch(&registers);
    decoder.parse(x, &registers, memory, labels);
    decoder.execute(&registers, x, memory);
    cout << setw(20) << left << x << " " << registers << endl;
  } // while eip != 0

  return 0;

} // main ()
