#ifndef INSTRUCTCONVERT
#define INSTRUCTCONVERT

#include <string>
#include <vector>
#include <map>

using namespace std;

// 만약에 헤더 파일에 map의 정의를 넣으려면 extern을 넣어야 컴파일 에러가 나지 않는다.
extern map<string, pair<unsigned int, unsigned int>> InstrInfo;

string InstrConvert_R(vector<string> instr);

string InstrConvert_I(vector<string> instr, unsigned int PC);

string InstrConvert_J(vector<string> instr);

string InstrConvert_Control(vector<string> instr, unsigned int PC);

#endif
