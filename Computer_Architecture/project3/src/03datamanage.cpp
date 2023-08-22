#include "../include/03datamanage.h"

#include <string>
#include <sstream>
#include <bitset>

using namespace std;

// 이 함수는 인자로 날것 숫자말고 unsigned int 형식의 변수만 받아야 한다.
// 그리고 signed 변수도 다뤄야 하니까 bool isSigned가 true이면 signed 형식의 변수를 집어넣는다.
string DecimalToHex(unsigned int dec, bool isSigned){
    stringstream temp;
    int temp_int = dec;
    if(isSigned)
        temp << hex << temp_int;
    else
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

bool StrIsNum(string str, bool isHex){
    for(long unsigned int i=0;i<str.size();i++){
        if((int)str[i] < 48 || (int)str[i] > 57){
            if((isHex && (str[i] == 'x')))
                continue;
            else if(isHex && ( (int)str[i] >= 65 && (int)str[i] <= 70 ))
                continue;
            else if(isHex && ( (int)str[i] >= 97 && (int)str[i] <= 102 ))
                continue;
            else 
                return false;
        }
    }
    return true;
}

// Bit 형태의 string을 받으면 이를 sign extend나 zero extend된 bit 형태의 string을 반환
string BitExtend(string num, unsigned int isSignEx){
    if(isSignEx==1){ // sign-extend
        if(num[0] == '0'){
            string temp(32 - num.length(), '0');
            return temp + num;
        }
        else{
            string temp(32 - num.length(), '1');
            return temp + num;
        }
    }
    else{ // zero-extend
        string temp(32-num.length(), '0');
        return temp + num;
    }
}