#ifndef FUNCTIONS
#define FUNCTIONS

#include "01containers.h"

#include <vector>

using namespace std;

// 예외처리 정의
class MainException { };
class argv_mem_exception : public MainException{ };
class argv_instrnum_exception : public MainException{ };
class atp_exception : public MainException{ };

// ALU control signal을 만들 때 사용되는 상수들
const unsigned int ADD=0b000;
const unsigned int SUB=0b001;
const unsigned int SHIFTLEFT=0b010;
const unsigned int SHIFTRIGHT=0b011;
const unsigned int SOLT=0b100;
const unsigned int AND=0b101;
const unsigned int OR=0b110;
const unsigned int NOR=0b111;

// 기본적으로 두개의 데이터를 받되, 필요한 경우 4개까지 받을 수 있도록 개조
// signal이 0 : data1, 1 : data2, 2: data3, 3: data4
int MUX(unsigned int signal, int data1, int data2, int data3=0, int data4=0);

// control signal을 만들어야 하는 statereg를 받아서 statereg를 집어넣는다
void CONTROL(StateReg* ifid);

int EX_ALU(int data1, int data2, int aluop);

// forwarding 두개를 합칠 수 있을거 같은데??? >> pointer를 사용하니 가능
// data forwarding을 다루는 함수
// mux에 전달해야 할 적절한 control signal을 반환해야 한다.
void DataForwardUnit(StateReg* statereg, StateReg* exmem, StateReg* memwb);

// hazard를 다루는 unit : load-use hazard, branch ID using hazard, atp hazard
void HazardUnit(StateReg* pc, StateReg* ifid, StateReg* idex, unsigned int isAtp);

// branch를 다루는 함수
// Reg를 받아올 필요가 없어졌다. 
unsigned int BranchHandler(StateReg* statereg, StateReg* exmem, unsigned int isAtp);



#endif