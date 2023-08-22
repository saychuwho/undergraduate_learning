#include "01_DataManage.h"
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

const unsigned int TEXT_START_ADDR = 0x00400000;
const unsigned int DATA_START_ADDR = 0x10000000;

map<string, int> data_label_addr;
map<string, int> text_label_addr;

// 이 함수는 인자로 날것 숫자말고 unsigned int 형식의 변수만 받아야 한다.
string DecimalToHex(unsigned int dec){
    stringstream temp;
    temp << hex << dec;
    string ResHex = "0x";
    ResHex += temp.str();
    return ResHex;
}

vector<string> SplitLine(string str, char seperator){
    istringstream tempstream(str);
    string tempstr;
    vector<string> ret;
    while(getline(tempstream, tempstr, seperator)){
        if(tempstr == "") continue;
        ret.push_back(tempstr);
    }
    return ret;
}

bool StrHaveChar(string str, char c){
    int str_size = str.length();
    for(int i=0;i<str_size;i++){
        if (str[i] == c )
            return true;
    }
    return false;
}

string NumToBit(string num, unsigned int size){
    int NumSource = stoi(num, nullptr, 0);
    bitset<32> tempBit(NumSource);
    string retStr = tempBit.to_string().substr(32-size);
    return retStr;
}