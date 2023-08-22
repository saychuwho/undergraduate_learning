#include "01datamanage.h"
#include "02doInstr.h"
#include "03memRegManage.h"


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

// memory, register 선언
map<unsigned int, int> Reg;
// 메모리 각 주소에는 bit로 변환된 string이 바이트 단위로 있다. 이들이 빅 엔디안 형식으로 저장되어있음.
// 메모리를 하나로 합쳐서 구현하자
map<unsigned int, string> Mem;
unsigned int PC;
const unsigned int TEXT_START_ADDR = 0x400000;
const unsigned int DATA_START_ADDR = 0x10000000;

// 예외처리 정의
class MainException { };
class argv_mem_exception : public MainException{ };
class argv_instrnum_exception : public MainException{ };

int main(int argc, char** argv){
    // 프로그램이 시작되자마자 register, memory, PC를 초기화한다
    PC = 0x400000;
    int zero = 0;
    // 메모리 시작값 초기화
    MemWrite(TEXT_START_ADDR, zero);
    MemWrite(DATA_START_ADDR, zero);
    // register 초기화
    for(int i=0;i<32;i++){
        Reg[i] = 0;
    }

    // 받은 argc의 수가 최대 수인 7개(./runfile, -m과 addr, -d, -n과 instnum, input file)을 넘어가면 프로그램을 종료
    if(argc > 7){
        cerr << "Error : too many argument" << endl;
        exit(1);
    }
    // argc를 받아서 옵션을 해석하는 부분
    bool isMemout = false;
    vector<string> printMemAddr;
    bool isPrintall = false;
    bool isInstLimit = false;
    unsigned int instrLimit = 0;
    string inputFileName = "";
    try{
        for(int i=1;i<argc;i++){
            if(strcmp(argv[i], "-m") == 0){
                isMemout = true;
                i++;
                if(!StrHaveChar(argv[i], ':')){
                    throw argv_mem_exception();
                }
                // 메모리 주소로 수가 아닌 다른게 들어오면 이거를 걸러내야 한다
                printMemAddr = SplitLine(argv[i], ':');
                if(!StrIsNum(printMemAddr.at(0), true) || !StrIsNum(printMemAddr.at(1), true)){
                    throw argv_mem_exception();
                }
                if(stoul(printMemAddr.at(0), nullptr, 0) > stoul(printMemAddr.at(1), nullptr, 0)){
                    throw argv_mem_exception();
                }
            }
            else if(strcmp(argv[i], "-d") == 0){
                isPrintall = true;
            }
            else if(strcmp(argv[i], "-n") == 0){
                isInstLimit = true;
                i++;
                if(!StrIsNum(argv[i])){
                    throw argv_instrnum_exception();
                }
                string tempStr = argv[i];
                instrLimit = stoul(tempStr);
            }
            else{
                inputFileName = argv[i];
            }
        }
    }
    catch(argv_mem_exception){
        cerr << "Error : invalid memory address" << endl;
        RegMemCout(false, printMemAddr);
        exit(1);
    }
    catch(argv_instrnum_exception){
        cerr << "Error : invalid instruction number to execute" << endl;
        RegMemCout(isMemout, printMemAddr);
        exit(1);
    }

    // 바이너리 파일을 받아서 읽는 곳
    ifstream inputBinaryFile;
    inputBinaryFile.open(inputFileName, ios::binary);
    // 파일을 읽을 수 없다면 프로그램을 종료한다
    if(!inputBinaryFile){
        cerr << "Error : can't open object file" << endl;
        RegMemCout(isMemout, printMemAddr);
        exit(1);
    }
    // 바이너리 파일을 받아서 라인 단위로 변환한다
    string temp = "";
    vector<string> binaryfileLine;
    while(getline(inputBinaryFile, temp)){
        binaryfileLine.push_back(temp);
    }
    inputBinaryFile.close();

    // 받은 바이너리 파일이 빈 파일인지, 유효한 파일인지 검사가 필요하다.
    unsigned int fileSize = binaryfileLine.size();
    // 빈 파일(아예 내용이 없거나, Text section size, data section size 조차 없는 경우)인지 검사한다
    if(fileSize < 2){
        RegMemCout(isMemout, printMemAddr);
        exit(0);
    }
    unsigned int textSize = stoul(binaryfileLine.at(0), nullptr, 0) / 4;
    unsigned int dataSize = stoul(binaryfileLine.at(1), nullptr, 0) / 4;
    // Data section과 Text section의 개수랑 파일의 전체 길이가 맞지 않는 경우는 배제해야 한다.
    if(textSize + dataSize != (fileSize-2)){
        cerr << "Error : Invalid object file" << endl;
        RegMemCout(isMemout, printMemAddr);
        exit(1);
    }
    
    // instruction과 data를 메모리에 저장한다. 적합한 파일일 경우에!!!
    for(unsigned int i=2;i<textSize+2;i++){
        MemWrite(TEXT_START_ADDR + 4*(i-2), stoul(binaryfileLine.at(i), nullptr, 0));
    }
    for(unsigned int i=fileSize-dataSize;i<fileSize;i++){
        MemWrite(DATA_START_ADDR + 4*(i-fileSize+dataSize), stoul(binaryfileLine.at(i), nullptr, 0));
    }
    // instruction을 수행하는 부분
    unsigned int instrCounter = 0;
    unsigned int progEndAddr = TEXT_START_ADDR + 4*textSize;
    while(PC<progEndAddr){// 기본적으로는 PC가 마지막 instruction 그 다음에 도달하면 이 과정을 멈추어야 한다 
        if(isInstLimit && instrLimit == instrCounter){ // -n 옵션이 들어왔을 때 instruction 수행을 멈춰야 한다.
            break;
        }
        instrCounter++;
        instrDecode();
        if(isPrintall){
            RegMemCout(isMemout, printMemAddr);
        }
    }

    RegMemCout(isMemout, printMemAddr);
    return 0;
}
