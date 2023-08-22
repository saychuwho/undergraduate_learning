#include "01datamanage.h"
#include "02doInstr.h"
#include "03memRegManage.h"

#include <map>
#include <vector>
#include <string>
#include <bitset>
#include <iostream>

void doInstr_R(string rs, string rt, string rd, string shamt, string funct){
    unsigned int tmp_rs = stoul(rs, nullptr, 2);
    unsigned int tmp_rt = stoul(rt, nullptr, 2);
    unsigned int tmp_rd = stoul(rd, nullptr, 2);
    unsigned int tmp_shamt = stoul(shamt, nullptr, 2);
    unsigned int tmp_funct = stoul(funct, nullptr, 2);
    if(tmp_funct == 0x21){ // addu
        Reg[tmp_rd] = Reg[tmp_rs] + Reg[tmp_rt];
        PC += 4;
    }
    else if(tmp_funct == 0x24){ // and
        Reg[tmp_rd] = Reg[tmp_rs] & Reg[tmp_rt];
        PC += 4;
    }
    else if(tmp_funct == 8){ // jr
        PC = Reg[tmp_rs];
    }
    else if(tmp_funct == 0x27){ // nor
        Reg[tmp_rd] = ~(Reg[tmp_rs] | Reg[tmp_rt]);
        PC += 4;
    }
    else if(tmp_funct == 0x25){ // or
        Reg[tmp_rd] = Reg[tmp_rs] | Reg[tmp_rt];
        PC += 4;
    }
    else if(tmp_funct == 0x2b){ // sltu
        if(Reg[tmp_rs] < Reg[tmp_rt])
            Reg[tmp_rd] = 1;
        else
            Reg[tmp_rd] = 0;
        PC += 4;
    }
    else if(tmp_funct == 0){ // sll
        Reg[tmp_rd] = Reg[tmp_rt] << tmp_shamt;
        PC += 4;
    }
    else if(tmp_funct == 2){ // srl
        Reg[tmp_rd] = Reg[tmp_rt] >> tmp_shamt;
        PC += 4;
    }
    else if(tmp_funct == 0x23){ // subu
        Reg[tmp_rd] = Reg[tmp_rs] - Reg[tmp_rt];
        PC += 4;
    }
}

void doInstr_I(string op, string rs, string rt, string immOffset){
    unsigned int tmp_op = stoul(op, nullptr, 2);
    unsigned int tmp_rs = stoul(rs, nullptr, 2);
    unsigned int tmp_rt = stoul(rt, nullptr, 2);
    if(tmp_op == 9){ // addiu
        Reg[tmp_rt] = Reg[tmp_rs] + stol(BitExtend(immOffset), nullptr, 2);
        PC += 4;
    }
    else if(tmp_op == 0xc){ // andi
        Reg[tmp_rt] = Reg[tmp_rs] & stol(BitExtend(immOffset, false), nullptr, 2);
        PC += 4;
    }
    else if(tmp_op == 4){ // beq
        unsigned int offset = stoul(immOffset, nullptr, 2);
        if(Reg[tmp_rs] == Reg[tmp_rt]){
            PC = PC + 4 + 4*offset;
        }
        else{
            PC += 4;
        }
    }
    else if(tmp_op == 5){ // bne
        unsigned int offset = stoul(immOffset, nullptr, 2);
        if(Reg[tmp_rs] != Reg[tmp_rt]){
            PC = PC + 4 + 4*offset;
        }
        else{
            PC += 4;
        }
    }
    else if(tmp_op == 0xf){ // lui
        string tmpExtend(16,'0');
        Reg[tmp_rt] = stol(immOffset + tmpExtend, nullptr, 2);
        PC += 4;
    }
    else if(tmp_op == 0x23){ // lw
        unsigned int offset = stoul(immOffset, nullptr, 2);
        // offset 만큼 더한 곳의 실제 그 메모리 주소로 가서 8비트를 로드했어야 한다
        Reg[tmp_rt] = MemLoad(Reg[tmp_rs] + 4*offset);
        PC += 4;
    }
    else if(tmp_op == 0x20){ // lb
        unsigned int offset = stoul(immOffset, nullptr, 2);
        int tmpVal = MemLoad(Reg[tmp_rs] + offset, false);
        bitset<8> tmpBit(tmpVal);
        Reg[tmp_rt] = stol(BitExtend(tmpBit.to_string()), nullptr, 2); // 이거 long으로 넣는 임시방편 말고 좀 더 정확한 방법이 있지 않을까???
        PC += 4;
    }
    else if(tmp_op == 0xd){ // ori
        Reg[tmp_rt] = Reg[tmp_rs] | stol(BitExtend(immOffset, false), nullptr, 2);
        PC += 4;
    }
    else if(tmp_op == 0xb){ // sltiu
        int tmp_extimm = stol(BitExtend(immOffset), nullptr, 2);
        if(Reg[tmp_rs]<tmp_extimm)
            Reg[tmp_rt] = 1;
        else{
            Reg[tmp_rt] = 0;
        }
        PC += 4;
    }
    else if(tmp_op == 0x2b){ // sw
        unsigned int offset = stoul(immOffset, nullptr, 2);
        MemWrite(Reg[tmp_rs] + 4*offset, Reg[tmp_rt]);
        PC += 4;
    }
    else if(tmp_op == 0x28){ // sb
        unsigned int offset = stoul(immOffset, nullptr, 2);
        string storeBit = NumToBit(to_string(Reg[tmp_rt]), 8);
        MemWrite(Reg[tmp_rs]+offset, stol(storeBit, nullptr, 2), false);
        PC += 4;
    }
}

void doInstr_J(string op, string target){
    // 주소는 target*4에 PC에서 사용되는 상위 4비트를 더하도록 구현해야 한다.
    unsigned int tmp_op = stoul(op, nullptr, 2);
    unsigned int tmp_target = stoul(target, nullptr, 2);
    bitset<28> bitAddr(tmp_target*4);
    bitset<32> bitPC(PC);
    string temp_addr = bitPC.to_string().substr(4) + bitAddr.to_string();
    unsigned int addr = stoul(temp_addr, nullptr, 2);
    if(tmp_op == 2){ // j 형식
        PC = addr;
    }
    else if(tmp_op == 3){ // jal 형식 : $ra는 R31이다
        Reg[31] = PC + 4; // 다음에 실행할 Instruction이니까 PC + 4
        PC = addr;
    }
}