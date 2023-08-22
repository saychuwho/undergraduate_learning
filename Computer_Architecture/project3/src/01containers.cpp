#include "01containers.h"
#include "03datamanage.h"

#include <map>
#include <vector>
#include <string>
#include <bitset>
#include <iostream>

Memory::Memory(unsigned int s_addr){
    start_addr = s_addr;
    mem[start_addr] = "0x0";
}

// isByte=0이면 word 단위로 store하고, 1이면 byte 단위로 store
void Memory::MemWrite(unsigned int addr, int value, unsigned int isByte){
    if(isByte==0){
        bitset<32> tempData(value);
        string tempDataStr = tempData.to_string();
        for(int i=0;i<4;i++){
            MemWrite(addr + i, stol(tempDataStr.substr(8*i, 8), nullptr, 2), 1);
        }
    }
    else{ // byte 단위로 write할 때
        bitset<8> tempData(value);
        mem[addr] = tempData.to_string();
    }
}

// isByte=0이면 word 단위로 load하고, 1이면 byte 단위로 load
int Memory::MemRead(unsigned int addr, unsigned int isByte){
    if(isByte==0){ // word 단위로 로드할 때 (기존 방식)
        if(mem.find(addr) != mem.end()){
            string temp_str = "";
            for(int i=0;i<4;i++){
                bitset<8> tempByte = MemRead(addr+i, 1);
                temp_str += tempByte.to_string();
            }
            return stol(temp_str, nullptr, 2);
        }
        else{
            return 0x0;
        }
    }
    else{ // byte 단위로 로드할 때
        if(mem.find(addr) != mem.end()){
            return stol(mem[addr], nullptr, 2);
        }
        else{
            return 0x0;
        }
    }
}

bool Memory::IsMemHave(unsigned int addr){
    if(mem.find(addr) == mem.end())
        return false;
    else
        return true;
}

Register::Register(){
    for(int i=0;i<32;i++){
        Reg[i] = 0;
    }
}

void Register::RegWrite(unsigned int regNum, int value){
    Reg[regNum] = value;
}

int Register::RegRead(unsigned int regNum){
    return Reg[regNum];
}

StateReg::StateReg(){ 
    Tag = NOOP;
}

StateReg::StateReg(unsigned int pcaddr){
    Tag = PC;
    PCaddr = pcaddr;
}

/*
프로그램이 완전히 끝났을 때는 다음을 출력해야 한다.
    - 얼마나 많은 pipeline cycle이 수행되었는가
    - 출력하는 시점에서 pipeline 상태
    - 프로그램이 종료되는 시점에서 레지스터의 내용
여기에다가 옵션이 들어가면 매 pipeline cycle마다 다음 내용을 출력해야 한다
    - -d : register 상태
    - -p : pipeline 상태
    - -m : memory 상태
    - cyclenum은 main에서 for문 돌아가는 iter를 넘겨받으면 됨.
굳이 pointer로 받아올 필요는 X : 값을 읽을 뿐이기 때문에*/
void statusCout(
    vector<StateReg*> pipeline, Memory textmem, Memory datamem, 
    Register reg, vector<string> printMemaddr,
    unsigned int cyclenum, bool ispipePrint, bool isregPrint, bool ismemout,bool isend)
{
    // cycle을 출력하는 부분 : isEnd 여부에 따라 출력 값이 달라진다.
    if(isend){
        cout << "===== Completion cycle: " << cyclenum << " =====" << endl;
        cout << endl;
    }
    else{   
        cout << "===== Cycle " << cyclenum << " =====" << endl;  
    }
    // pipeline state를 출력하는 부분
    if(ispipePrint || isend){ // PipePrint가 켜져있거나 프로그램 종료시 작동
        cout << "Current pipeline PC state:" << endl;
        vector<string> pipelineAddr;
        for(long unsigned int i=0;i<pipeline.size();i++){
            if(pipeline.at(i)->Tag == NOOP){
                pipelineAddr.push_back("");
            }
            else{
                pipelineAddr.push_back(DecimalToHex(pipeline.at(i)->PCaddr));
            }
        }
        cout << "{";
        for(vector<string>::iterator i=pipelineAddr.begin();i!=pipelineAddr.end();i++){
            cout << *i;
            if(i != pipelineAddr.end() - 1)
                cout << "|";
        }
        cout << "}" << endl;
        cout << endl;
    }

    // Register 속 값들을 출력하는 부분
    if(isregPrint || isend){
        cout << "Current register values:" << endl;
        cout << "PC: " << DecimalToHex(reg.PC) << endl;
        cout << "Registers:" << endl;
        for(int i=0;i<32;i++){
            cout << "R" << i << ": " << DecimalToHex(reg.RegRead(i)) << endl;
        }
        cout << endl;
    }

    // mem 속 값들을 출력하는 부분
    if(ismemout){
        cout << "Memory content [" << printMemaddr.at(0) << ".." << printMemaddr.at(1) << "]" << endl;
        cout << "-------------------------------------------" << endl;
        unsigned int printMemStart = stoul(printMemaddr.at(0), nullptr, 0);
        unsigned int printMemLast = stoul(printMemaddr.at(1), nullptr, 0);
        for (unsigned int i=0;i<((printMemLast - printMemStart) / 4 + 1);i++){
            unsigned int temp_addr = printMemStart + 4*i;
            string temp_value = "0x0";
            if(textmem.IsMemHave(temp_addr)){
                temp_value = DecimalToHex(textmem.MemRead(temp_addr, 0));
            }
            else if(datamem.IsMemHave(temp_addr)){
                temp_value = DecimalToHex(datamem.MemRead(temp_addr, 0));
            }
            cout << DecimalToHex(temp_addr) << ": " << temp_value << endl;
        }
        cout << endl;
    }
}