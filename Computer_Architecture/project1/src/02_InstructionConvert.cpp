#include "01_DataManage.h"
#include "02_InstructionConvert.h"
#include "03_CodeManage.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

// map에 instruction들의 op와 funct를 넣자. 
// unsigned int 첫번째는 op, 두번째는 R형식일 경우 funct, 아니면 0으로 넣는다. 
map<string, pair<unsigned int, unsigned int>> InstrInfo{
    {"addiu", make_pair(9,0)}, {"addu", make_pair(0,0x21)}, 
    {"and", make_pair(0,0x24)}, {"andi", make_pair(0xc,0)}, 
    {"beq", make_pair(4,0)}, {"bne", make_pair(5,0)},
    {"j", make_pair(2,0)}, {"jal", make_pair(3,0)},
    {"jr", make_pair(0,8)}, {"lui", make_pair(0xf,0)},
    {"lw", make_pair(0x23,0)},{"lb", make_pair(0x20,0)},
    {"nor", make_pair(0,0x27)},{"or", make_pair(0,0x25)},
    {"ori", make_pair(0xd,0)},{"sltiu", make_pair(0xb,0)},
    {"sltu", make_pair(0,0x2b)},{"sll", make_pair(0,0)},
    {"srl", make_pair(0,2)},{"sw", make_pair(0x2b,0)},
    {"sb", make_pair(0x28,0)},{"subu", make_pair(0,0x23)},
};

// instr 안에는 연산자, rd, rs, rt가 들어온다. 
// instr 안에 있는 rd, rs, rt가 "$_," 형식으로 들어온다고 가정하고 짜자. 이건 다른 함수들도 마찬가지라고 생각하자.
// string 속 integer 값을 unsigned 값으로 내놓는 함수는 stoul이다. 안전을 위해서 stoi를 stoul로 바꾸고, base=0으로 해 type을 auto detect 하도록 했다.
// stoul(string, ptr, base)를 사용할 때, ptr에 nullptr등의 pointer를 따로 지정하지 않으면 base=0이 제대로 작동하지 않는다.
string InstrConvert_R(vector<string> instr){
    string converted_instr = "";
    unsigned int temp_converted_instr = 0;
    // shift 연산을 사용하기 위해 모두 unsigned int로 지정해둔다.
    unsigned int op = InstrInfo[instr.at(0)].first;
    unsigned int rs = 0;
    unsigned int rt = 0;
    unsigned int rd = 0;
    unsigned int shamt = 0;
    unsigned int funct = InstrInfo[instr.at(0)].second;
    
    // 레지스터 주소가 instr 안에 "$__," 처럼 저장되어 있으니, substr()를 이용해 레지스터 주소만 뽑아낸다
    // R형식의 예외사항이 sll, slb도 있었다...
    if (instr.at(0) == "jr"){
        rs = stoul(instr.at(1).substr(1, instr.at(1).length() - 1),nullptr,0);
    } 
    else if(instr.at(0) == "sll" || instr.at(0) == "srl"){
        rs = 0;
    }
    else{
        rs = stoul(instr.at(2).substr(1, instr.at(2).length() - 2),nullptr,0);
    } 
    if(instr.at(0) != "jr"){
        if(instr.at(0) == "sll" || instr.at(0) == "srl"){
            rt = stoul(instr.at(2).substr(1, instr.at(2).length() - 2),nullptr,0);
            shamt = stoul(instr.at(3),nullptr,0);
        }
        else
            rt = stoul(instr.at(3).substr(1, instr.at(3).length() - 1),nullptr,0);
        rd = stoul(instr.at(1).substr(1, instr.at(1).length() - 2),nullptr,0);
    }
    temp_converted_instr = (op << 26) + (rs << 21) + (rt << 16) + (rd << 11) + (shamt << 6) + funct;
    
    converted_instr = DecimalToHex(temp_converted_instr);


    return converted_instr;
}

// I형식은 imm 부분에서 const가 들어올수도 있어서 수들을 모두 비트로 변환한 string으로 바꾼 뒤 이를 이용해 연산하자.
string InstrConvert_I(vector<string> instr, unsigned int PC){
    string converted_instr = "";
    unsigned int temp_converted_instr = 0;
    string op = NumToBit(to_string(InstrInfo[instr.at(0)].first), 6);
    string rs = "";
    string rt = "";
    // const일 경우 당연히 signed일거고, offset도 이제보니 signed이네....
    string imm_or_offset = "";
    // offset(rs) 형식의 instruction인가 아닌가로 구분
    if(StrHaveChar(instr.at(2),'(')){
        // offset과 rs를 분리할 필요가 있다.
        vector<string> sep_offset_rs = SplitLine(instr.at(2), '(');
        imm_or_offset = NumToBit(sep_offset_rs.at(0), 16);
        rs = NumToBit(sep_offset_rs.at(1).substr(1, sep_offset_rs.at(1).length() - 2), 5);
        rt = NumToBit(instr.at(1).substr(1, instr.at(1).length() - 2), 5);
    }
    else{
        // rs를 지정하는 곳
        // LUI는 rs = 0이고 rt만 있다.
        if (instr.at(0) == "lui")
            rs = "00000";
        // BEQ와 BNE는 들어올 때 rs, rt의 순서가 다른 I와는 반대다.
        else if (instr.at(0) == "beq" || instr.at(0) == "bne")
            rs = NumToBit(instr.at(1).substr(1, instr.at(1).length() - 2), 5);
        else
            rs = NumToBit(instr.at(2).substr(1, instr.at(2).length() - 2), 5);

        // rt를 지정하는 곳
        // BEQ와 BNE는 들어올 때 rs, rt의 순서가 다른 I와는 반대다.
        if (instr.at(0) == "beq" || instr.at(0) == "bne") 
            rt = NumToBit(instr.at(2).substr(1, instr.at(2).length() - 2), 5);
        else
            rt = NumToBit(instr.at(1).substr(1, instr.at(1).length() - 2),5);
        
        // imm을 지정하는 곳
        // LUI는 rt, imm만 받는다.
        if (instr.at(0) == "lui")
            imm_or_offset =  NumToBit(instr.at(2), 16);
        // bne, beq는 offset을 계산해서 넣어야 한다.
        else if(instr.at(0) == "beq" || instr.at(0) == "bne"){
            int offset = (stoi(instr.at(3), nullptr, 0) - PC - 4) / 4;
            imm_or_offset = NumToBit(to_string(offset), 16);
        }
        else{
            imm_or_offset =  NumToBit(instr.at(3), 16);
        }
    }
    temp_converted_instr = stoul(op+rs+rt+imm_or_offset, nullptr, 2);
    converted_instr = DecimalToHex(temp_converted_instr);
    

    return converted_instr;
}

string InstrConvert_J(vector<string> instr){ 
    string converted_instr = "";
    unsigned int temp_converted_instr = 0;
    unsigned int op = InstrInfo[instr.at(0)].first;
    unsigned int target = stoul(instr.at(1),nullptr, 0) / 4;
    temp_converted_instr = (op << 26) + target;
    converted_instr = DecimalToHex(temp_converted_instr);
    
    return converted_instr;
}

// 명령어의 종류에 맞춰서 instruction convert 함수를 불러온다.
// 여기서 넘어오는 PC는 명령어의 주소이다.
string InstrConvert_Control(vector<string> instr, unsigned int PC){
    string ret_hex_instruction;
    if(InstrInfo[instr.at(0)].first == 0)
        ret_hex_instruction = InstrConvert_R(instr);
    else if(InstrInfo[instr.at(0)].first == 2 || InstrInfo[instr.at(0)].first == 3)
        ret_hex_instruction = InstrConvert_J(instr);
    else
        ret_hex_instruction = InstrConvert_I(instr, PC);
    return ret_hex_instruction;
}