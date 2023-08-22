#ifndef CONTAINERS
#define CONTAINERS

#include <vector>
#include <map>
#include <string>

using namespace std;

// 메모리 시작 주소를 나타내는 상수
const unsigned int TEXT_START_ADDR = 0x400000;
const unsigned int DATA_START_ADDR = 0x10000000;

// Tag로 사용되는 상수들을 정의해둬 헷갈리지 않게 하자.
const unsigned int NOOP = 0;
const unsigned int PC = 1;
const unsigned int IFID = 2;
const unsigned int IDEX = 3;
const unsigned int EXMEM = 4;
const unsigned int MEMWB = 5;

class Memory{
protected:
    // 메모리 생긴거는 이전처럼 내부적으로 string으로 처리하자.
    map<unsigned int, string> mem;
    unsigned int start_addr;
public:
    // 생성되면서 메모리 시작 값을 초기화해야 한다.
    Memory(unsigned int s_addr);
    // 이 부분은 project2 코드랑 유사하니까 거기서 들고와서 수정하면 될 듯.
    void MemWrite(unsigned int addr, int value, unsigned int isByte);
    int MemRead(unsigned int addr, unsigned int isByte);
    // 메모리에 실제로 이 주소가 있는가? 있으면 true, 없으면 false
    bool IsMemHave(unsigned int addr);
};

class Register{
private:
    map<unsigned int, int> Reg;
public:
    // 생성할 때 모든 레지스터 값을 0으로 초기화하는 과정이 필요
    // 이 PC는 실제 Register에 있는 PC
    // IF stage의 statereg가 아니다.
    unsigned int PC=TEXT_START_ADDR;
    Register();
    void RegWrite(unsigned int regNum, int value);
    int RegRead(unsigned int regNum);
};


// StateReg를 struct로 다시 만들자.
class StateReg{
public:
    // stage tag (noop=0, PC=1, IFID=2, IDEX=3, EXMEM=4, MEMWB=5)
    unsigned int Tag = 0;
    // stall을 나타내는 변수 : stall이 반영되어 pipeline stage가 설정되면 stall을 다시 0으로 만들어야 한다
    // stall의 의미는 "본인이 앞으로 가고 본인 뒤에 있던 거는 멈춘 채로 그 뒤에는 Noop을 집어넣는것" 이다.
    unsigned int stall = 0;
    // flush를 나타내는 변수 : flush가 반영되면 다시 0으로 바꾸어야 한다.
    // flush의 의미는 "본인이 앞으로 가고, 본인 뒤에 있는 모든 StateReg를 없애고 Noop을 집어넣는 것"이다.
    unsigned int flush = 0;
    
    // PC
    unsigned int PCaddr = 0;
    
    // IF가 끝난 후 나오는 값
    unsigned int instruction = 0;
    unsigned int op = 0;
    unsigned int rs = 0;
    unsigned int rt = 0;
    unsigned int rd = 0;
    int imm = 0; // 여기에는 R형식의 shamt, J형식의 target도 있다.
    unsigned int funct = 0;

    // ID가 끝난 후 생기는 값
    int regData1 = 0;
    int regData2 = 0;
    // jal이나, atp에서 beq, bne의 예측된 jump addr
    unsigned int IDjumpAddr = 0;
    
    // EX가 끝난 후 생기는 값
    int aluResult = 0;

    // MEM이 끝난 후
    int memData = 0;

    // control signal들(ID에서 control unit이 추가하는) 여기에(생각나는대로 추가)
    // 아래 세개 : 0이면 안씀, 1이면 씀
    unsigned int MemWrite = 0;
    unsigned int MemRead = 0;
    unsigned int RegWrite = 0;
    unsigned int ALUop = 0;
    // WB에서 rt가 write인지(1) rd가 write인지(0) 결정
    unsigned int RegDST = 0;
    // mem에서 word 단위로 다루는지 여부를 결정(0이면 word단위, 1이면 byte)
    unsigned int MemByte = 0;
    // ALU에 들어가는 data2를 Regdata2에서 들고오는지(0), imm에서 들고오는지(1) 결정
    unsigned int ALUsrc = 0;
    // ALU에 들어가는 data1을 Regdata1(0)에서 들고오는지 Regdata2(1)에서 들고오는지
    unsigned int ALUsrc2 = 0;
    // WB stage에서 값을 저장할 때, aluResult(0)를 저장할 지, memData(1)를 저장할지를 결정
    unsigned int RegWriteSource = 0;
    // 이 StateReg에서 사용되는 값에서 rs 혹은 rt에서 forwarding이 필요한가?
    // (0) 필요없음, (1) exmem에서 forwarding (2) memwb에서 forwarding
    unsigned int rsForwarding = 0;
    unsigned int rtForwarding = 0;


    // ID stage에서 바로 사용되는 control signal
    // i형식에서만 extend 할 필요가 있지, shamt, target은 extend하면 안된다.
    // 0이면 imm값을 zero extend, 1이면 sign-extend, 2면 imm이 아니니까 아무 기능도 하지 마.
    unsigned int isSignExtend = 0;
    // branch handler에게 넘겨야 하는가?
    // (0) 안 넘긴다 (1) 넘긴다(jump) (2) 넘긴다(branch)
    unsigned int Branch = 0;

    // 생성자 : noop을 표현
    StateReg();
    // 생성자 : PCaddr에 PC를 넣고, tag를 1로 만든다.
    StateReg(unsigned int pcaddr);
};

// 현재 status를 출력하는 역할을 담당한다.
void statusCout(
    vector<StateReg*> pipeline, Memory textmem, Memory datamem, 
    Register reg, vector<string> printMemaddr,
    unsigned int cyclenum, bool ispipePrint, bool isregPrint, bool ismemout,bool isend=false);

#endif