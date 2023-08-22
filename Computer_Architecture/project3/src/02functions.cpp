#include "01containers.h"
#include "02functions.h"

int MUX(unsigned int signal, int data1, int data2, int data3, int data4){
    if(signal==0)
        return data1;
    else if(signal==1)
        return data2;
    else if(signal==2)
        return data3;
    else
        return data4;
}

// 이거를 모든 instruction에 대해 일일이 다 만드는게 더 편할려나....
// 모든 경우에 대해서 만드는게 더 편할 듯
// branch는 branch handler를 만들어서 거기서 처리해야 할 듯. 여기는 branch가 아닌 control을 만들고
// ALUop에 그냥 판단을 담자.
void CONTROL(StateReg* ifid){
    // branch가 있을 경우는 branch handler에게 넘겨야 하니 branch factor를 1로 만들어야 한다.
    if(ifid->op==2 || ifid->op==3){ // j형식
        ifid->Branch = 1;
        // 둘 다 target에 extend 같은게 없어야 한다!
        ifid->isSignExtend = 2;
        if(ifid->op == 3){ // jal의 경우는 return address를 31번 register에 저장해야 하므로 이를 반영한 control signal을 추가로 적어주어야 한다.
            ifid->RegWrite = 1;
            ifid->rd = 31;
            ifid->ALUsrc = 1;
        }
    }
    // EX에서 연산된 결과를 가지고 branch 후 jump를 해야 하니 이를 반영해서 control signal을 주어야 한다. 
    else if(ifid->op== 4 || ifid->op==5){ // beq, bne
        ifid->Branch = 2;
        ifid->ALUop = SUB;
    }
    else if(ifid->op == 0 && ifid->funct == 8){ // jr
        ifid->Branch = 1;
    }
    // R형식 : funct에 따라서 ALUop를 만들어내야 한다.
    else if(ifid->op == 0){
        // 공통부분
        ifid->RegWrite = 1;
        // shamt에도 extend가 없어야 한다
        ifid->isSignExtend = 2;
        if(ifid->funct == 0x21){ // addu
            ifid->ALUop = ADD;
        }
        else if(ifid->funct == 0x24){
            ifid->ALUop = AND;
        }
        else if(ifid->funct == 0x27){ // nor
            ifid->ALUop = NOR;
        }
        else if(ifid->funct == 0x25){ // or
            ifid->ALUop = OR;
        }
        else if(ifid->funct == 0x2b){ // sltu
            ifid->ALUop = SOLT;
        }
        else if(ifid->funct == 0){ // sll
            ifid->ALUop = SHIFTLEFT;
            ifid->ALUsrc = 1;
            ifid->ALUsrc2 = 1;
        }
        else if(ifid->funct == 2){ // srl
            ifid->ALUop = SHIFTRIGHT;
            ifid->ALUsrc = 1;
            ifid->ALUsrc2 = 1;
        }
        else{ //subu
            ifid->ALUop = SUB;
        }
    }
    // I형식
    else{
        // 공통부분
        ifid->ALUsrc = 1;
        ifid->RegDST = 1;
        ifid->RegWrite = 1;
        if(ifid->op == 9){ // addiu
            ifid->ALUop = ADD;
            ifid->isSignExtend = 1;
        }
        else if(ifid->op == 0xc){ // andi
            ifid->ALUop = AND;
        }
        else if(ifid->op == 0xf){ // lui
            // shift left 16번하면 될거 같은데
            // ex에서 수동으로 값을 설정하자.
            ifid->ALUop = SHIFTLEFT;
        }
        else if(ifid->op == 0x23){ // lw
            ifid->ALUop = ADD;
            ifid->MemRead = 1;
            ifid->RegWriteSource = 1;
        }
        else if(ifid->op == 0x20){ // lb
            ifid->ALUop = ADD;
            ifid->MemRead = 1;
            ifid->MemByte = 1;
            ifid->RegWriteSource = 1;
        }
        else if(ifid->op == 0xd){ // ori
            ifid->ALUop = OR;
        }
        else if(ifid->op == 0xb){ //sltiu
            ifid->ALUop = SOLT;
        }
        else if(ifid->op == 0x2b){ // sw
            ifid->ALUop = ADD;
            ifid->MemWrite = 1;
            ifid->RegWrite = 0;
        }
        else if(ifid->op == 0x28){ // sb
            ifid->ALUop = ADD;
            ifid->MemWrite = 1;
            ifid->MemByte = 1;
            ifid->RegWrite = 0;
        }
    }
}

// ALU가 수행해야 하는 연산
// 해당하는 연산 타입들은 모두 상수로 지정되어있다.로 지정되었다.
// 3bit로 표현 가능! 잘 매칭해서 alucon을 만들어내고 이걸 받아서 연산처리하면 됨.
int EX_ALU(int data1, int data2, int aluop){
    if(aluop == ADD){
        return data1 + data2;
    }
    else if(aluop == SUB){
        return data1 - data2;
    }
    else if(aluop == SHIFTLEFT){
        return data1 << data2;
    }
    else if(aluop == SHIFTRIGHT){
        return data1 >> data2;
    }
    else if(aluop == SOLT){
        if(data1 < data2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(aluop == AND){
        return data1 & data2;
    }
    else if(aluop == OR){
        return data1 | data2;
    }
    else{
        return ~(data1 | data2);
    }
}

// 출력하는 control signal은 1이면 exmem에서 forwarding, 2면 memwb에서 forwarding
// 그냥 forwarding signal도 StateReg 안에 저장하는 걸로 처리하자. branch handler에서도 써먹어야 한다.
void DataForwardUnit(StateReg* statereg, StateReg* exmem, StateReg* memwb){
    // reset을 하고 다시 판단할 필요가 있다.
    statereg->rsForwarding = 0;
    statereg->rtForwarding = 0;
    // idex와 exmem에서 forwarding, jr 계산할 때 forwarding을 구현해야 한다.
    if(statereg->Tag == IDEX || statereg->Tag == EXMEM || (statereg->op == 0 && statereg->funct == 8)){ 
        // exmem에서 statereg로의 forwarding을 고려하는 상황
        if(statereg->Tag != EXMEM && exmem->Tag != 0 && exmem->RegWrite != 0){ // exmem -> idex이나 ifid가 jr일때만 고려해야 한다.
            // RegDST에 따라서 비교해야 할 register가 달라지니 이를 구분
            // 그리고 forwarding을 당할 register에 대한 정보도 저장해둬야 한다.
            if(exmem->RegDST == 0 && exmem->aluResult != 0){ // exmem이 rd에 뭔가를 쓰는 상황일 때
                if(exmem->rd != 0 && (exmem->rd == statereg->rs))
                    statereg->rsForwarding = 1;
                if(exmem->rd != 0 && (exmem->rd == statereg->rt))
                    statereg->rtForwarding = 1;
            }
            else if(exmem->RegDST == 1){ // exmem이 rt에 뭔가를 쓰는 상황일 때
                if(exmem->rt != 0 && (exmem->rt == statereg->rs))
                    statereg->rsForwarding = 1;
                if(exmem->rt != 0 && (exmem->rt == statereg->rt))
                    statereg->rtForwarding = 1;
            }
        }
        // memwb에서 forwarding을 고려하는 상황 >> idex랑 memwb에서 이를 고려해야 한다.
        // exmem에서 forwarding이 이루어지지 않는다면... (이거는 idex일때만)
        if(memwb->Tag != 0 && memwb->RegWrite == 1){
            if(memwb->RegDST == 0){ // memwb이 rd에 뭔가를 쓰는 상황일 때
                if(statereg->Tag == IDEX){ // memwb->idex
                    // exmem->RegWrit==0이거나, exmem->rd != memwb->rd이거나, exmem->RegDST==1인데 exmem->rt != memwb->rd이면
                    if((exmem->RegWrite == 0) || (exmem->rd != memwb->rd) || ((exmem->RegDST == 1) && (memwb->rd != exmem->rt))) {
                        if(memwb->rd != 0 && (memwb->rd == statereg->rs)) // memwb의 rd가 0이 아니고, memwb의 rd와 statereg의 rs가 같을 때
                            statereg->rsForwarding = 2;
                        if(memwb->rd != 0 && (memwb->rd == statereg->rt)) // memwb의 rd가 0이 아니고, memwb의 rd와 statereg의 rt가 같을 때
                            statereg->rtForwarding = 2;
                    }
                }
                else{ // memwb->exmem
                    if(memwb->rd != 0 && (memwb->rd == statereg->rs)) // memwb의 rd가 0이 아니고, memwb의 rd와 statereg의 rs가 같을 때
                        statereg->rsForwarding = 1;
                    if(memwb->rd != 0 && (memwb->rd == statereg->rt)) // memwb의 rd가 0이 아니고, memwb의 rd와 statereg의 rt가 같을 때
                        statereg->rtForwarding = 1;
                }
            }
            else if(memwb->RegDST == 1){ // memwb이 rt에 뭔가를 쓰는 상황일 때
                if(statereg->Tag == IDEX){ // memwb->idex
                    // exmem->RegWrit==0이거나, exmem->rd != memwb->rt이거나, exmem->RegDST==1인데 exmem->rt != memwb->rt이면
                    if((exmem->RegWrite == 0) || ((exmem->RegDST == 0)&&(exmem->rd != memwb->rt)) || ((exmem->RegDST == 1) && (memwb->rt != exmem->rt))) {
                        if(memwb->rt != 0 && (memwb->rt == statereg->rs)) // memwb의 rt가 0이 아니고, memwb의 rt와 statereg의 rs가 같을 때
                            statereg->rsForwarding = 2;
                        if(memwb->rt != 0 && (memwb->rt == statereg->rt)) // memwb의 rt가 0이 아니고, memwb의 rt와 statereg의 rt가 같을 때
                            statereg->rtForwarding = 2;
                    }
                }
                else{ // memwb->exmem
                    if(memwb->rt != 0 && (memwb->rt == statereg->rs)) // memwb의 rd가 0이 아니고, memwb의 rd와 statereg의 rs가 같을 때
                        statereg->rsForwarding = 1;
                    if(memwb->rt != 0 && (memwb->rt == statereg->rt)) // memwb의 rd가 0이 아니고, memwb의 rd와 statereg의 rt가 같을 때
                        statereg->rtForwarding = 1;
                }
            }
        }
    }
}

// stall이나 flush 여부는 StateReg 안에 tag를 붙여서 구분하자.
// 그리고 추후 pipeline이 끝날 때 stall tag나 flush tag가 있으면 그에 따라 행동하도록 설계하자.
void HazardUnit(StateReg* pc, StateReg* ifid, StateReg* idex, unsigned int isAtp){
    // load-use hazard : load한 데이터를 EX에서 사용할 때 생기는 hazard. >> control signal에서 따로 추가하자.
    // i형식의 경우 load의 rt와 rs가 같은지, r형식의 경우 load의 rs, rt가 같은지, j형식의 경우 rt와 31이 같은지 여부를 확인해야 한다.
    if(idex->MemRead == 1){
        if(ifid->op == 0){ // r형식의 경우
            if(ifid->rs == idex->rt || ifid->rt == idex->rt)
                idex->stall = 1;
        }
        else if(ifid->op == 2 || ifid->op == 3){ // j형식의 경우 상관 X
            idex->stall = 0;
        }
        else{ // i형식의 경우
            if(ifid->rs == idex->rt)
                idex->stall = 1;
        }
    }
    if((pc->op == 4 || pc->op == 5) && isAtp == 1){
        // always taken prediction일 경우에는 ID에서 주소를 계산한 이후 pc를 받아와야 하므로 stall cycle이 한번 필요하다.
        if(isAtp == 1)
            pc->stall = 1;
    }

    // jr의 경우는 beq, bne와는 다르게 atp 여부와는 상관없이 hazard가 발생할 수 있으니 stall을 한번 넣어야 한다.
    if(pc->op == 0 && pc->funct == 8){
        if(ifid->RegWrite == 1){
            if((pc->rs == ifid->rt) && (ifid->RegDST == 1))
                ifid->stall = 1;
            else if((pc->rs == ifid->rd) && ifid->RegDST == 0)
                ifid->stall = 1;
        }
    }

    // 점프 instruction은 control hazard를 근본적으로 피하기 위해 그 이후에 stall을 한번 집어넣어야 한다.
    // pc는 control signal이 생기기 전이니까 op로 판단을 해야 한다. 
    if(pc->op == 2 || pc->op == 3){
        pc->stall = 1;
    }
}

// 일단 반환해야 하는 값은 jump하는 address이다.
// ID에서 계산해야 할 일은 atp이면 beq, bne의 jump addr을 계산한 후 IDjumpAddr에 저장하고 그 주소를 반환해서 jump 될 수 있도록 만들어야 한다.
// ID에서 antp일 경우에는 jump가 아니면 pass 한다.
// ID에서는 jump가 들어오면 무조건 그에 상응하는 jump addr을 반환해야 한다. 이때, jal일 경우에는 계산된 주소를 imm에 저장해 Register에 담기도록 해야 한다.
unsigned int BranchHandler(StateReg* statereg, StateReg* exmem, unsigned int isAtp){ 
    unsigned int RetjumpAddr = 0;
    // 기존에 짰던 부분 : ID에서 branch 주소를 계산하는 부분이다.
    if(statereg->Tag == IFID){ // ifid에서 branch prediction
        StateReg* ifid = statereg;
        // Reg 값을 불러올 때는 forwarding 여부에 따라서 값을 불러와야 한다.
        if(ifid->Branch == 2){ // beq와 bne (atp 일때만 주소를 계산해서 반환해야 한다)
            // 새로 짠 코드 : atp인 경우에 주소를 반환한다.
            unsigned int tempJumpAddr = (ifid->PCaddr + 4) + ifid->imm*4;
            if(isAtp == 1){ // atp인 경우에는 이를 반환해준다.
                RetjumpAddr = tempJumpAddr;
                ifid->IDjumpAddr = tempJumpAddr;
            }
        }
        // Jump instruction은 애초에 stall을 집어넣어서 control hazard를 해결해야 하니 flush가 없어야 한다.
        else if(ifid->op == 2){ // j
            RetjumpAddr = ifid->imm << 2;
            // ifid->flush = 1;
        }
        else if(ifid->op == 3){ // jal : 이 경우는 돌아올 주소(PC+4)를 저장해두어야 한다.
            RetjumpAddr = ifid->imm << 2;
            ifid->imm = ifid->PCaddr + 4;
            // ifid->flush = 1;
        }
        else if(ifid->op == 0){ // jr >> 어차피 이 함수가 불렸다는 의미는 branch 명령어 밖에 없다는 뜻이다.
            RetjumpAddr = MUX(ifid->rsForwarding, ifid->regData1, exmem->aluResult);
            // ifid->flush = 1;
        }
    }
    // 새로 짜야 할 부분. beq, bne의 계산된 주소가 예측한 주소와 동일한지를 판단하고 flush를 넣을지 말지를 판단하는 부분.
    // beq, bne에서는 주소계산 자체의 hazard는 존재하지 않는다.
    else if(statereg->Tag == EXMEM){ // MEM에서 branch 계산 후 판단
        unsigned int tempJumpAddr = 0;
        if(statereg->op == 4 && statereg->aluResult == 0){ // beq에서 taken 되는 경우
            tempJumpAddr = (statereg->PCaddr + 4) + statereg->imm*4;
        }
        else if(statereg->op == 5 && statereg->aluResult != 0){ // bne에서 taken 되는 경우
            tempJumpAddr = (statereg->PCaddr + 4) + statereg->imm*4;
        }

        if(statereg->IDjumpAddr != tempJumpAddr){ // 예측에 실패한 경우 : taken 되지 않았어야 하므로 exmem->PCAddr + 4로 jump한다.
            statereg->flush = 1;
            if(isAtp == 1) // atp이면 taken되지 않았을 때 주소로 가야함.
                RetjumpAddr = statereg->PCaddr + 4;
            else // antp이면 taken되었을 때 주소로 가야함.
                RetjumpAddr = tempJumpAddr;
        }
        else{ // 예측에 성공한 경우 : 그냥 0을 return하고 종료한다.
            RetjumpAddr = 0;
        }
    }
    return RetjumpAddr;
}

