#ifndef DATAMANAGE
#define DATAMANAGE

#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

string DecimalToHex(unsigned int dec);

vector<string> SplitLine(string str, char seperator);

bool StrHaveChar(string str, char c);

string NumToBit(string num, unsigned int size);

#endif