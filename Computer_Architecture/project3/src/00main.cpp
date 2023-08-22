#include "01containers.h"
#include "02functions.h"
#include "03datamanage.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <bitset>

int main(int argc, char** argv){
    // debug시에만 사용 : 제출하기 전에는 반드시!!! 모든 debug 변수들을 false로 해놓고 제출할것.
    bool DEBUG = false; // general한 debug
    bool DEBUG2 = false; // PipelineStage와 instrcounter를 표시 등 control 관련 debug
    bool DEBUG_CYCLE = false; // branch에서 오류가 나서 무한루프에 빠지는 것을 방지.
    const int DEBUG_CYCLENUM = 70;

    // 사용되는 register, mem, statereg를 초기화하는 곳
    Memory TextMem(TEXT_START_ADDR);
    Memory DataMem(DATA_START_ADDR);
    Register Reg;
    // pipeline stage를 표현하는 vector
    // 최초 초기화시에는 dummy로 가득 채운다.
    StateReg noop;
    vector<StateReg*> PipelineStage;
    for(int i=0;i<5;i++){
        PipelineStage.push_back(&noop);
    }

    // argument들을 받아서 option들을 지정하는 곳
    // 받은 argc의 수가 최대 수인 9개    
    if(argc > 9){
        cerr << "Error : too many argument" << endl;
        exit(1);
    }
    // argc를 받아서 옵션을 해석하는 부분
    unsigned int AtpOrAntp = 0; // -atp(1) or -antp(2) : 만약에 argument를 끝까지 받았음에도 이게 0이면 오류를 내고 프로그램을 종료
    bool isMemout = false; // -m
    vector<string> printMemAddr; // -m에서 출력할 메모리 주소 범위를 저장
    bool isRegPrint = false; // -d
    bool isInstLimit = false; // -n
    unsigned int instrLimit = 0; // -n에서 수행할 명령어의 개수
    bool isPipePrint = false; // -p
    string inputFileName = "";
    bool printEveryCycle = false; // cycle마다 출력해야 할 내용이 하나라도 있으면 true로 바꿈
    int cycleCounter = -1; // 밑에서 instruction을 수행할 때 사용됨.

    try{
        for(int i=1;i<argc;i++){
            if(strcmp(argv[i], "-atp") == 0){
                AtpOrAntp = 1;
            }
            else if(strcmp(argv[i],"-antp") == 0){
                AtpOrAntp = 2;
            }
            else if(strcmp(argv[i], "-m") == 0){
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
                isRegPrint = true;
                printEveryCycle = true;
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
            else if(strcmp(argv[i], "-p") == 0){
                isPipePrint = true;
                printEveryCycle = true;
            }
            else{
                inputFileName = argv[i];
            }
        }
        if(AtpOrAntp == 0){
            throw atp_exception();
        }
    }
    catch(argv_mem_exception){
        cerr << "Error : invalid memory address" << endl;
        statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, true);
        exit(1);
    }
    catch(argv_instrnum_exception){
        cerr << "Error : invalid instruction number to execute" << endl;
        statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, true);
        exit(1);
    }
    catch(atp_exception){
        cerr << "Error : atp option is missing" << endl;
        statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, true);
        exit(1);
    }


    // 파일을 읽은 후 메모리에 로드(project2에서 들고옴)
    // 바이너리 파일을 받아서 읽는 곳
    ifstream inputBinaryFile;
    inputBinaryFile.open(inputFileName, ios::binary);
    // 파일을 읽을 수 없다면 프로그램을 종료한다
    if(!inputBinaryFile){
        cerr << "Error : can't open object file" << endl;
        statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, true);
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
        statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, true);
        exit(0);
    }
    unsigned int textSize = stoul(binaryfileLine.at(0), nullptr, 0) / 4;
    unsigned int dataSize = stoul(binaryfileLine.at(1), nullptr, 0) / 4;
    // Data section과 Text section의 개수랑 파일의 전체 길이가 맞지 않는 경우는 배제해야 한다.
    if(textSize + dataSize != (fileSize-2)){
        cerr << "Error : Invalid object file" << endl;
        statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, true);
        exit(1);
    }
    

    // instruction과 data를 메모리에 저장한다. 적합한 파일일 경우에!!!
    
    for(unsigned int i=2;i<textSize+2;i++){
        TextMem.MemWrite(TEXT_START_ADDR + 4*(i-2), stoul(binaryfileLine.at(i), nullptr, 0), 0);
        
    }
    
    for(unsigned int i=fileSize-dataSize;i<fileSize;i++){
        DataMem.MemWrite(DATA_START_ADDR + 4*(i-fileSize+dataSize), stoul(binaryfileLine.at(i), nullptr, 0),0);
    }
    


    // instruction들을 수행하는 공간

    unsigned int instrCounter = 0;
    unsigned int progEndAddr = TEXT_START_ADDR + 4*textSize;
    bool isEnd = false; // pipeline이 이번 cycle 이후 모두 끝났는지를 indicate
    bool stopPC = false; // fetch를 더이상 해야 하는지 여부를 indicate
    // Pipeline Stage이 시작하기 전에 IF에는 초기 PC값으로 채워넣어야 한다
    // PipelineStage.at(0) = new StateReg(Reg.PC);
    // jumpAddr은 while문 안에서 초기화되면 안된다.
    unsigned int jumpAddr = 0;

    // debuging 용 counter
    int debugCounter = 0;

    bool isflush = false;
    bool isStall = false;

    // debug
    if(DEBUG2){
        cout << DecimalToHex(progEndAddr) << " progEndAddr" << endl;
    }


    while(!isEnd){ // 기본적으로는 PC가 마지막 instruction 그 다음에 도달하면 이 과정을 멈추어야 한다 
        debugCounter++;
        
        // 여기에 포인터 값들을 담아둬서 알기 쉽도록 만들어놓자.
        StateReg* stPC = PipelineStage.at(0);
        StateReg* ifid = PipelineStage.at(1);
        StateReg* idex = PipelineStage.at(2);
        StateReg* exmem = PipelineStage.at(3);
        StateReg* memwb = PipelineStage.at(4);

        // debug
        if(DEBUG2){
            cout << endl;
            cout << "--Pipeline Stages--" << endl;
            for(int i=0;i<5;i++)
                cout << DecimalToHex(PipelineStage.at(i)->PCaddr) << ":" << PipelineStage.at(i)->Tag << endl;
            cout << endl;
        }
        
        // -n에서 지정된 instruction 개수 만큼 실행이 완료된 이후 종료해야 하므로 이때는 break한다.
        // instrCounter는 MEMWB 속 instruction이 delete 될 때 증가되어야 한다.
        if(isInstLimit && instrLimit == instrCounter){
            isEnd = true;
            break;
        }
        // 위 구문들이 다 아니면, cycle을 수행하니 이때 counter를 올려야 한다.
        else
            cycleCounter++;
        
        if(DEBUG_CYCLE){
            if(debugCounter > DEBUG_CYCLENUM)
                break;
        }
        
        // 이 자리에서 열심히 pipeline이 반영된 일들을 뽕짝뽕짝 수행해야 함.
        // IF stage : 지난번 코드에서 instrdecode를 좀 손본 후 사용하면 될 듯.
        if(stPC->Tag != 0){ // NOOP이 아닐 때 이걸 수행해야 한다.
            stPC->instruction = TextMem.MemRead(stPC->PCaddr, 0);
            bitset<32> tmpDecodeBit(stPC->instruction);
            string tmpDecodeStr = tmpDecodeBit.to_string();
            unsigned int tmp_op = stoul(tmpDecodeStr.substr(0, 6), nullptr, 2);
            stPC->op = tmp_op;
            if(tmp_op == 0){ // R형식
                stPC->rs = stoul(tmpDecodeStr.substr(6, 5), nullptr, 2);
                stPC->rt = stoul(tmpDecodeStr.substr(11, 5), nullptr, 2);
                stPC->rd = stoul(tmpDecodeStr.substr(16, 5), nullptr, 2);
                stPC->imm = stoul(tmpDecodeStr.substr(21, 5), nullptr, 2); // shamt
                stPC->funct = stoul(tmpDecodeStr.substr(26), nullptr, 2);
            }
            else if(tmp_op == 2 || tmp_op == 3){ // J형식
                stPC->imm = stoul(tmpDecodeStr.substr(6), nullptr, 2); // shamt
            }
            else{ // I형식
                stPC->rs = stoul(tmpDecodeStr.substr(6, 5), nullptr, 2);
                stPC->rt = stoul(tmpDecodeStr.substr(11, 5), nullptr, 2);
                stPC->imm = stoul(tmpDecodeStr.substr(16), nullptr, 2); // imm or offset
            }

            // debug
            if(DEBUG){
                cout << endl;
                cout << "--IF stage--" << endl;
                cout << DecimalToHex(stPC->PCaddr) << endl;
                cout << stPC->op << " op decimal" << endl;
                cout << DecimalToHex(stPC->op) << " op hex" << endl;
                cout << stPC->rs << " rs" << endl;
                cout << stPC->rt << " rt" << endl;
                cout << stPC->rd << " rd" << endl;
                cout << stPC->imm << " imm" << endl;
                cout << DecimalToHex(stPC->funct) << " funct hex" << endl;
                cout << endl;
            }
        }

        // WB stage : Register에 먼저 값을 집어넣어야 한다.
        if(memwb->Tag != 0 && memwb->RegWrite != 0){
            unsigned int wbReg = MUX(memwb->RegDST, memwb->rd, memwb->rt);
            int wbData = MUX(memwb->RegWriteSource, memwb->aluResult, memwb->memData);
            Reg.RegWrite(wbReg, wbData);
            
            //debug
            if(DEBUG){
                cout << "--WB stage--" << endl;
                cout << DecimalToHex(memwb->PCaddr) << endl;
                cout << DecimalToHex(wbReg) << " " << DecimalToHex(wbData) << endl;
            }
        }
        

        // ID stage
        if(ifid->Tag != 0){
            // control signal을 만들어내기
            CONTROL(ifid);

            // Dataforwarding 여부를 판단 
            //forwarding이 필요가 없어졌는데??? >> jr 때문에 필요하다.
            DataForwardUnit(ifid, exmem, memwb);
            
            // Branch가 아니여도 밑의 것들은 공통적으로 수행해야 한다.
            ifid->regData1 = Reg.RegRead(ifid->rs);
            ifid->regData2 = Reg.RegRead(ifid->rt);
            // 이전에 썼던 함수들을 유의하면서 imm의 bit extend를 해야 한다.
            // R형식의 shamt나 J형식의 target은 bit extend 할 필요가 없다. 
            if(ifid->isSignExtend != 2){
                string tmpimm = DecimalToHex(ifid->imm, true);
                tmpimm = NumToBit(tmpimm, 16);
                tmpimm = BitExtend(tmpimm, ifid->isSignExtend);
                if(ifid->isSignExtend == 0){
                    ifid->imm = stoul(tmpimm, nullptr, 2);
                }
                else{
                    ifid->imm = stol(tmpimm, nullptr, 2);
                }
            }

            // Branch이면 branch handler에게 넘기기
            // 기존 BranchHandler를 수정해서, beq, bne의 atp일 때 예측 주소를 계산해서 반환하고, jump 관련 계산에서는 jump를 실제로 수행하도록 만들자.
            if(ifid->Branch != 0)  
                jumpAddr = BranchHandler(ifid, exmem, AtpOrAntp);
            

            //debug
            if(DEBUG){
                cout << endl;
                cout << "--ID stage--" << endl;
                cout << DecimalToHex(ifid->PCaddr) << endl;
                cout << ifid->MemWrite << " MemWrite" << endl;
                cout << ifid->MemRead << " MemRead" << endl;
                cout << ifid->RegWrite << " RegWrite" << endl;
                cout << ifid->ALUop << " ALUop" << endl;
                cout << ifid->RegDST << " RegDST" << endl;
                cout << ifid->MemByte << " MemByte" << endl;
                cout << ifid->ALUsrc << " ALUsrc" << endl;
                cout << ifid->ALUsrc2 << " ALUsrc2" << endl;
                cout << ifid->RegWriteSource << " RegWriteSource" << endl;
                cout << ifid->rsForwarding << " rsForwarding" << endl;
                cout << ifid->rtForwarding << " rtForwarding" << endl;
                cout << ifid->isSignExtend << " isSignExtend" << endl;
                cout << ifid->Branch << " Branch" << endl;
                cout << ifid->regData1 << " regData1" << endl;
                cout << ifid->regData2 << " regData2" << endl;
                cout << DecimalToHex(jumpAddr) << " jumpAddr hex" << endl;
                cout << jumpAddr << " jumpAddr decimal" << endl;
                cout << DecimalToHex(ifid->IDjumpAddr) << " IDjumpAddr hex" << endl;
                cout << ifid->IDjumpAddr << " IDjumpAddr decimal" << endl;
                cout << endl;
            }
        }

        // Hazard 여부를 판단
        HazardUnit(stPC, ifid, idex, AtpOrAntp);
        // debug
        if(DEBUG){
            cout << endl;
            cout << "--Hazard--" << endl;
            cout << stPC->stall << " " << DecimalToHex(stPC->PCaddr) << " stPC stall" << endl;
            cout << ifid->stall << " " << DecimalToHex(ifid->PCaddr) << " ifid stall" << endl;
            cout << ifid->flush << " " << DecimalToHex(ifid->PCaddr) << " ifid flush" << endl;
            cout << idex->stall << " " << DecimalToHex(idex->PCaddr) << " idex stall" << endl;
            cout << endl;
        }

        // EX stage
        if(idex->Tag != 0){
            // Dataforwarding 여부를 판단
            DataForwardUnit(idex, exmem, memwb);
            // memwb에서 어떤 데이터를 들고올것인가.... (MemRead에 따라서 결정해야 한다!)
            int tmpMemWbData = MUX(memwb->MemRead, memwb->aluResult, memwb->memData);
            // 첫번째 mux 판단에서는 forwarding만 우선적으로 판단하자
            int tmpData1 = MUX(idex->rsForwarding, idex->regData1, exmem->aluResult, tmpMemWbData);
            int tmpData2 = MUX(idex->rtForwarding, idex->regData2, exmem->aluResult, tmpMemWbData);
            // 여기서 ALUsrc에 따라서 실제로 ALU data로 들어가는게 무엇인지 판단
            int ALUdata1 = MUX(idex->ALUsrc2, tmpData1, tmpData2);
            int ALUdata2 = MUX(idex->ALUsrc, tmpData2, idex->imm);
            if(idex->op == 0xf){ //lui는 수동으로 설정하자.
                ALUdata1 = idex->imm;
                ALUdata2 = 16;
            }
            idex->aluResult = EX_ALU(ALUdata1, ALUdata2, idex->ALUop);

            // debug
            if(DEBUG){
                cout << endl;
                cout << "--EX stage--" << endl;
                cout << DecimalToHex(idex->PCaddr) << endl;
                cout << idex->rsForwarding << " rsForwarding" << endl;
                cout << idex->rtForwarding << " rtForwarding" << endl;
                cout << tmpData1 << " tmpData1" << endl;
                cout << tmpData2 << " tmpData2" << endl;
                cout << ALUdata1 << " ALUdata1" << endl;
                cout << ALUdata2 << " ALUdata2" << endl;
                cout << idex->aluResult << " aluResult" << endl;
                cout << endl;
            }
        }
        
        // MEM stage
        if(exmem->Tag != 0){
            // dataforwarding 여부를 계산
            DataForwardUnit(exmem, &noop, memwb);
            // MemRead
            if(exmem->MemRead != 0){
                exmem->memData = DataMem.MemRead(exmem->aluResult, exmem->MemByte);
            }
            // MemWrite
            if(exmem->MemWrite != 0){
                int WBdata = MUX(memwb->RegWriteSource, memwb->aluResult, memwb->memData);
                int tmpMemData = MUX(exmem->rtForwarding, exmem->regData2, WBdata);
                DataMem.MemWrite(exmem->aluResult, tmpMemData, exmem->MemByte);
            }

            // branch 여부를 계산
            if(exmem->Branch == 2){
                jumpAddr = BranchHandler(exmem, &noop, AtpOrAntp);
            }

            //debug
            if(DEBUG){
                cout << endl;
                cout << "--MEM stage--" << endl;
                cout << DecimalToHex(exmem->PCaddr) << endl;
                cout << exmem->rsForwarding << " rsForwarding" << endl;
                cout << exmem->rtForwarding << " rtForwarding" << endl;
                cout << exmem->aluResult << " aluResult(value)" << endl;
                cout << DecimalToHex(exmem->aluResult) << " aluResult(addr)" << endl;
                cout << exmem->memData << " memData : decimal" << endl;
                cout << DecimalToHex(exmem->memData) << " memData : hex" << endl;
                cout << exmem->regData2 << " regData2 : decimal" << endl;
                cout << DecimalToHex(exmem->regData2) << " regData2 : hex" << endl;
                cout << DecimalToHex(jumpAddr) << " jumpAddr : hex" << endl;
                cout << exmem->flush << " exmem flush" << endl;
                cout << endl;
            }
        }

        // jumpAddr이 0이면 Reg.PC에 jumpAddr을, 아니면 PC + 4를 해야 한다.
        // stall이나 flush 되는 거에 따라 증가하면 안될수도 있는데 이거....
        if(jumpAddr != 0){
            Reg.PC = jumpAddr;
        }
        else if(stPC->Tag != 0 && !stopPC && !isStall) // stPC 속 instruction이 noop이면 PC가 증가해서는 안된다.
            Reg.PC += 4;

        // 만약 Reg.PC == progEndAddr 이면 Fetch를 그만해야 한다.
        // progEndAddr이 이 주소부터는 instruction이 없다는 의미로 해석해야 한다.
        // 즉, Reg.PC는 증가하면 안되지만, jumpAddr이 생겨서 jump해야 한다면 jump해야 한다.
        if(Reg.PC == progEndAddr)
            stopPC = true;

        if(DEBUG){
            cout << endl;
            cout << "--PC state--" << endl;
            cout << DecimalToHex(jumpAddr) << " jumpAddr" << endl;
            cout << DecimalToHex(Reg.PC) << " Reg.PC" << endl;
            cout << endl;
        }

        // jump를 반영한 후에는 jumpAddr을 0으로 초기화해야 한다.
        jumpAddr = 0;

        if(printEveryCycle && cycleCounter != 0){ // cycle마다 출력할 게 있다면 출력해야 함.
            statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout);
        }


        /* instruction의 이동 : 기본적으로 Tag를 1 더하고 앞으로 한칸씩 옮기되, 
        stall이나 flush할 상황이 있으면 이를 반영한다. 
        그 이후 Reg.PC값에 따라 새로운 StateReg를 new로 동적할당 한다.*/
        
        isflush = false;
        isStall = false;

        for(int i=0;i<5;i++){
            int tmpnum = 4-i;
            if(tmpnum == 4){ //memwb을 바꾸어야 한다.
                if(PipelineStage.at(tmpnum)->Tag != 0){ // noop이 아닌 instruction이 들어있을 시
                    delete PipelineStage.at(tmpnum);
                    instrCounter++;
                }
            }
            else if(isStall){ // stall이면 가만히 있어야지.
                continue;
            }
            else if(isflush && tmpnum > 0){ // flush이면 IF에서 fetch하는 마지막을 제외하고는 모두 &noop으로 채운다.
                if(PipelineStage.at(tmpnum)->Tag != 0){
                    delete PipelineStage.at(tmpnum);
                    PipelineStage.at(tmpnum) = &noop;
                }
            }
            // 그 외 instruction : 마지막을 채우기 전 or PipelineStage의 마지막 instruction인데 stall인 경우.
            else if(tmpnum > 0 || ((tmpnum == 0) && (PipelineStage.at(0)->stall != 0) && !isflush)){ 
                // 일단 앞으로 댕긴다.
                if(PipelineStage.at(tmpnum)->Tag != 0)
                    PipelineStage.at(tmpnum)->Tag++;
                PipelineStage.at(tmpnum+1) = PipelineStage.at(tmpnum); 
                
                if(PipelineStage.at(tmpnum)->stall != 0){ // 이 instruction 뒤에 stall을 넣어야 할 경우
                    isStall = true;
                    PipelineStage.at(tmpnum)->stall--; // stall이 1 또는 2가 있으므로 그때마다 집어넣어야 한다.
                    i++;
                    PipelineStage.at(tmpnum) = &noop;
                }
                if(PipelineStage.at(tmpnum)->flush == 1){
                    isflush = true;
                    PipelineStage.at(tmpnum)->flush = 0;
                    PipelineStage.at(tmpnum) = &noop;
                }
            }
            else if(tmpnum == 0){ // fetch할 PC값을 담아서 동적할당한다.
                // flush가 아니면 일단 앞으로 댕긴다.
                if(!isflush){
                    if(PipelineStage.at(tmpnum)->Tag != 0)
                        PipelineStage.at(tmpnum)->Tag++;
                    PipelineStage.at(tmpnum+1) = PipelineStage.at(tmpnum); 
                }
                if(isflush){
                    if(PipelineStage.at(tmpnum)->Tag != 0)
                        delete PipelineStage.at(tmpnum);
                }

                if(!stopPC) // PC를 멈추는 경우가 아니라면 계속 Reg.PC 값을 fetch해야 한다.
                    PipelineStage.at(tmpnum) = new StateReg(Reg.PC);
                else if(stopPC && Reg.PC != progEndAddr){ // PC가 멈췄지만, 마지막 instruction이 끝나기 전에 다른 instruction에서 jump가 일어난다면, 
                    PipelineStage.at(tmpnum) = new StateReg(Reg.PC);
                    // 다시 instruction을 fetch하니까 true로 바꾸어야 한다.
                    stopPC = false;
                }
                else
                    PipelineStage.at(tmpnum) = &noop;
            }
        }

        // 새로운 종료방법 : Reg.PC == progEndAddr이고 Pipeline에 모든 것들이 비어있으면 isEnd를 true로 바꾼다.
        int isEndcounter = 5;
        if(Reg.PC == progEndAddr){
            for(int i=0;i<5;i++){
                if(PipelineStage.at(i)->Tag == 0)
                    isEndcounter--;
            }
            if(isEndcounter == 0){
                isEnd = true;
            }
        }

        if(DEBUG2){
            cout << endl;
            cout << isEndcounter << " isEndcounter" << endl;
            cout << endl;
        }

        if(DEBUG2){
            cout << endl;
            cout << textSize << " textSize" << endl;
            cout << instrCounter << " instrCounter" << endl;
            cout << debugCounter << " debugCounter" << endl;
            cout << endl;
        }
    }

    statusCout(PipelineStage, TextMem, DataMem, Reg, printMemAddr, cycleCounter, isPipePrint, isRegPrint, isMemout, isEnd);

    return 0;
}