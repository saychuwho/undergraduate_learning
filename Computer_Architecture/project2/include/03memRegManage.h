#ifndef MEMREGMANAGE
#define MEMREGMANAGE

#include <map>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

extern unsigned int PC;
extern const unsigned int TEXT_START_ADDR;
extern const unsigned int DATA_START_ADDR;
extern map<unsigned int, int> Reg;
extern map<unsigned int, string> Mem;
extern bitset<8> zeroBit;


void RegMemCout(bool isMemout, vector<string> pMemaddr);

void instrDecode();

int MemLoad(unsigned int addr, bool isWord=true);

void MemWrite(unsigned int addr, int value, bool isWord=true);

#endif