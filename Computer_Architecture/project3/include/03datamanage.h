#ifndef DATAMANAGE
#define DATAMANAGE

#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

string DecimalToHex(unsigned int dec, bool isSigned=false);

vector<string> SplitLine(string str, char seperator);

bool StrHaveChar(string str, char c);

string NumToBit(string num, unsigned int size);

// 선언부에서만 기본값을 정의해야 한다
bool StrIsNum(string str, bool isHex=false);

string BitExtend(string num, unsigned isSignEx);

#endif