#include "01datamanage.h"
#include "02doInstr.h"
#include "03memRegManage.h"

#include <iostream>
#include <map>
#include <string>
#include <bitset>

using namespace std;


void RegMemCout(bool isMemout, vector<string> pMemaddr){
    // 공통부분
    cout << "Current register values :" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "PC: " << DecimalToHex(PC) << endl;
    // register 값들을 출력하는 부분
    cout << "Registers:" << endl;
    for(map<unsigned int, int>::iterator i=Reg.begin();i!=Reg.end();i++){
        cout << "R" << i->first << ": " << DecimalToHex(i->second, true) << endl;
    }
    // memory를 출력하도록 세팅이 되었다면 메모리 속 값들을 출력
    if(isMemout){
        cout << endl;
        cout << "Memory content [" << pMemaddr.at(0) << ".." << pMemaddr.at(1) << "]" << endl;
        cout << "-------------------------------------------" << endl;
        unsigned int printMemStart = stoul(pMemaddr.at(0), nullptr, 0);
        unsigned int printMemLast = stoul(pMemaddr.at(1), nullptr, 0);
        for (unsigned int i=0;i<((printMemLast - printMemStart) / 4 + 1);i++){
            unsigned int temp_addr = printMemStart + 4*i;
            string temp_value = "";
            // temp addr에 실제로 해당하는 값이 있는지 확인. 해당하는 값이 없으면 0x0을 출력
            if(Mem.find(temp_addr) != Mem.end()){
                temp_value = DecimalToHex(MemLoad(temp_addr));
            }
            else{
                temp_value = "0x0";
            }
            cout << DecimalToHex(temp_addr) << ": " << temp_value << endl;
        }
    }
}

void instrDecode(){
    // decode 할 instruction을 불러오는 부분
    bitset<32> tmpDecodeBit(MemLoad(PC));
    string tmpDecodeStr = tmpDecodeBit.to_string();
    string tmp_op = tmpDecodeStr.substr(0, 6);
    if(stoul(tmp_op, nullptr, 2) == 0){ // R형식
        string tmp_rs = tmpDecodeStr.substr(6, 5);
        string tmp_rt = tmpDecodeStr.substr(11, 5);
        string tmp_rd = tmpDecodeStr.substr(16, 5);
        string tmp_shamt = tmpDecodeStr.substr(21, 5);
        string tmp_funct = tmpDecodeStr.substr(26);
        doInstr_R(tmp_rs, tmp_rt, tmp_rd, tmp_shamt, tmp_funct);
    }
    else if(stoul(tmp_op, nullptr, 2) == 2 || stoul(tmp_op, nullptr, 2) == 3){ // J형식
        string tmp_target = tmpDecodeStr.substr(6);
        doInstr_J(tmp_op, tmp_target);
    }
    else{ // I형식
        string tmp_rs = tmpDecodeStr.substr(6, 5);
        string tmp_rt = tmpDecodeStr.substr(11, 5);
        string tmp_immOffset = tmpDecodeStr.substr(16);
        doInstr_I(tmp_op, tmp_rs, tmp_rt, tmp_immOffset);
    }
}

// int 형태의 주소를 받아서 메모리 속 값을 반환하는 함수 : bit load 기능도 같춰야 한다....
// 메모리에 바이트 단위로 저장되어야 한다....... >> unsigned int 주소가 들어오면 비트 스트링으로 저장된 메모리의 값을 
// 비이트 단위로 반환할 것이냐 워드 단위로 반환할 것이냐에 따라서 반환을 달리 해야 한다.
// 이거도 안전하게 하려면 재귀로 호출을 해야 한다!
int MemLoad(unsigned int addr, bool isWord){
    if(isWord){ // word 단위로 로드할 때 (기존 방식)
        if(Mem.find(addr) != Mem.end()){
            string temp_str = "";
            for(int i=0;i<4;i++){
                bitset<8> tempByte = MemLoad(addr+i, false);
                temp_str += tempByte.to_string();
            }
            return stol(temp_str, nullptr, 2);
        }
        else{
            return 0x0;
        }
    }
    else{ // byte 단위로 로드할 때
        if(Mem.find(addr) != Mem.end()){
            return stol(Mem[addr], nullptr, 2);
        }
        else{
            return 0x0;
        }
    }
}

// bit 단위로 저장을 해야 하니 들어온 값이 word이면 이거를 bit string으로 바꾸서 8개 단위로 저장하고, bit면 그냥 저장한다.
// 여기도 안전하게 구현하려면 재귀로 구현해야 한다.
void MemWrite(unsigned int addr, int value, bool isWord){
    if(isWord){ // word 단위로 write할 때(기존방식)
        bitset<32> tempData(value);
        string tempDataStr = tempData.to_string();
        for(int i=0;i<4;i++){
            MemWrite(addr + i, stol(tempDataStr.substr(8*i, 8), nullptr, 2), false);
        }
    }
    else{ // byte 단위로 write할 때
        bitset<8> tempData(value);
        Mem[addr] = tempData.to_string();
    }
}