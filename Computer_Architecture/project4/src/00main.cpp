#include "../include/03datamanage.h"
#include "01cache.h"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

// 예외처리 정의
class MainException { };
class argv_capacity_exception : public MainException{ };
class argv_asso_exception : public MainException{ };
class argv_blocksize_exception : public MainException{ };
class lru_Invalid_exception : public MainException{ };

// total access 등등을 기록하는 변수
unsigned long totalAccess = 0;
unsigned long readAccess = 0;
unsigned long writeAccess = 0;

// debug시에만 사용 : 제출하기 전에는 반드시!! 모든 debug 변수들을 false로 해놓고 제출할 것.
bool DEBUG = false; // general한 debug
bool DEBUG_2 = false; // specific debug
bool DEBUG_3 = false; // 진행상황을 보기 위한 거 : 제출할때는 반드시 false로 해놓자.
bool DEBUG_4 = false; // 파일을 출력할 때 상황 파악을 위한 debug
bool DEBUG_5 = false; // 파일에 total counter를 출력하는 bool : 제출할때는 반드시 false로 해놓자.
unsigned long long traceCounter = 0; // trace를 해석할 때, counter

int main(int argc, char** argv){
    
    // 입력에서 받아오는 argument들을 정리
    unsigned int CAPACITY = 0;
    unsigned int ASSOCIATIVITY = 0;
    unsigned int BLOCK_SIZE = 0;
    // 1이면 lru, 2이면 random, 0이면 오류를 내뿜어
    unsigned int IS_LRU = 0;
    string TRACEFILE = "";

    // argument들을 받아서 option들을 지정하는 곳
    // 받은 argc의 수가 최대 수인 9개
    if(argc > 9){
        cerr << "Error : too many argument" << endl;
        exit(1);
    }
    
    try{
        for(int i=1;i<argc;i++){
            if(strcmp(argv[i], "-c") == 0){
                i++;
                if(!StrIsNum(argv[i]))
                    throw argv_capacity_exception(); // 숫자가 아닌게 들어오면 종료.
                else{
                    string tempstr = argv[i];
                    CAPACITY = stoul(tempstr, nullptr, 0);
                }
            }
            else if(strcmp(argv[i], "-a") == 0){
                i++;
                if(!StrIsNum(argv[i]))
                    throw argv_asso_exception(); // 숫자가 아닌게 들어오면 종료.
                else{
                    string tempstr = argv[i];
                    ASSOCIATIVITY = stoul(tempstr, nullptr, 0);
                }
            }
            else if(strcmp(argv[i], "-b") == 0){
                i++;
                if(!StrIsNum(argv[i]))
                    throw argv_blocksize_exception(); // 숫자가 아닌게 들어오면 종료.
                else{
                    string tempstr = argv[i];
                    BLOCK_SIZE = stoul(tempstr, nullptr, 0);
                }
            }
            else if(strcmp(argv[i], "-lru") == 0){
                IS_LRU = 1;
            }
            else if(strcmp(argv[i], "-random") == 0){
                IS_LRU = 2;
            }
            else{
                string tempstr = argv[i];
                TRACEFILE = tempstr;
            }
        }
        if(IS_LRU == 0){
            throw lru_Invalid_exception();
        }
    }
    catch(argv_capacity_exception){
        cerr << "Error : invalid capacity" << endl;
        exit(1);
    }
    catch(argv_asso_exception){
        cerr << "Error : invalid asso" << endl;
        exit(1);
    }
    catch(argv_blocksize_exception){
        cerr << "Error : invalid blocksize" << endl;
        exit(1);
    }
    catch(lru_Invalid_exception){
        cerr << "Error : no -lru option" << endl;
        exit(1);
    }


    // 파일을 읽은 후 메모리에 로드(project2에서 들고옴)
    // 바이너리 파일을 받아서 읽는 곳
    ifstream inputBinaryFile;
    inputBinaryFile.open(TRACEFILE, ios::binary);
    // 파일을 읽을 수 없다면 프로그램을 종료한다
    if(!inputBinaryFile){
        cerr << "Error : can't open object file" << endl;
        exit(1);
    }
    

    // cache들을 init하는 곳
    unsigned int l2_asso = ASSOCIATIVITY;
    unsigned int l1_asso = l2_asso / 4;
    unsigned int l2_cap = CAPACITY;
    unsigned int l1_cap = l2_cap / 4;
    if(ASSOCIATIVITY <= 2){
        l1_asso = l2_asso;
    }

    Block emptyBlock;
    Block* emptyBlock_pointer = &(emptyBlock);

    Cache* l1 = new L1Cache(l1_cap, l1_asso, BLOCK_SIZE, IS_LRU, emptyBlock_pointer);
    Cache* l2 = new L2Cache(l2_cap, l2_asso, BLOCK_SIZE, IS_LRU, emptyBlock_pointer);


    l1->init_cache_pointer(l2);
    l2->init_cache_pointer(l1);


    // 바이너리 파일 한 줄마다 해당하는 action을 수행한다.
    string temp = "";
    while(getline(inputBinaryFile, temp)){
        // 여기서 cache들의 동작이 수행된다.
        traceCounter++;
        //if(DEBUG && traceCounter % 10000 == 0){
        if(DEBUG || DEBUG_2){
            cout << endl;
            cout << "Trace [" << traceCounter << "] passed" << endl;
        }

        // 진행상황을 보기 위한 코드
        if(DEBUG_3 && traceCounter % 1000000 == 0){
            cout << "Trace [" << traceCounter << "] passed" << endl;
        }

        // 한 줄을 받았을 때, 그 줄을 나누어야 한다. datamanage에 있는 splitline을 사용하면 될 듯.
        vector<string> memInfo = SplitLine(temp, ' ');
        

        // access 횟수를 지정하는 곳
        totalAccess++;
        if(memInfo.at(0) == "R")
            readAccess++;
        else if(memInfo.at(0) == "W")
            writeAccess++;

    
        // access를 하자!
        Block* dummy = l1->access_addr(memInfo);

    }
    inputBinaryFile.close();
    
    if(DEBUG_3) cout << "is it done?" << endl;

    // 모든 동작들이 수행된 이후 최종 결과를 출력한다
    fstream output;
    // 출력되는 결과들은 모두 workloadName_capacity_associativity_blockSize.out의 형식으로 출력되어야 한다.
    // capacity : 입력된 cache의 용량 associativity : 입력된 associativity blocksize : 입력된 block size
    string output_filename = TRACEFILE.substr(0,TRACEFILE.length()-4);
    output_filename  = output_filename + "_" + to_string(CAPACITY);
    output_filename  = output_filename + "_" + to_string(ASSOCIATIVITY);
    output_filename  = output_filename + "_" + to_string(BLOCK_SIZE) + ".out";
    output.open(output_filename, ios::out);

    if(output.is_open()){
        // 각종 cache의 정보들을 여기에 출력하면 된다.
        output << "-- General Stats --" << endl;
        output << "L1 Capacity: " << l1->cache_size << endl;
        output << "L1 way: " << l1->asso_way << endl;
        output << "L2 Capacity: " << CAPACITY << endl;
        output << "L2 way: " << l2->asso_way << endl;
        output << "Block Size: " << BLOCK_SIZE << endl;
        output << "Total accesses: " << totalAccess << endl;
        output << "Read accesses: " << readAccess << endl;
        output << "Write accesses: " << writeAccess << endl;
        output << "L1 Read misses: " << l1->readMiss << endl;
        output << "L1 Write misses: " << l1->writeMiss << endl;
        output << "L2 Read misses: " << l2->readMiss << endl;
        output << "L2 Write misses: " << l2->writeMiss << endl;

        if(DEBUG_4) cout << "is it done1?" << endl;
        
        output << "L1 Read miss rate: " << ( static_cast<double>(l1->readMiss) / readAccess) * 100 << "%" << endl;

        if(DEBUG_4) cout << "is it done2?" << l1->readMiss << endl;

        output << "L2 Read miss rate: " << (static_cast<double>(l2->readMiss) / l1->readMiss) * 100 << "%" <<endl;

        if(DEBUG_4) cout << "is it done3?"  << endl;

        output << "L1 Write miss rate: " << ( static_cast<double>(l1->writeMiss) / writeAccess) * 100 << "%" <<endl;

        if(DEBUG_4) cout << "is it done4?" << endl;

        output << "L2 Write miss rate: " << (static_cast<double>(l2->writeMiss) / l1->writeMiss) * 100 << "%" <<endl;

        if(DEBUG_4) cout << "is it done5?" << endl;

        output << "L1 Clean eviction: " << l1->cleanEviction << endl;
        output << "L2 Clean eviction: " << l2->cleanEviction << endl;
        output << "L1 dirty eviction: " << l1->dirtyEviction << endl;
        output << "L2 dirty eviction: " << l2->dirtyEviction << endl;
        if(DEBUG_5){
            output << "total read miss rate : " << (static_cast<double>(l2->readMiss) / readAccess) * 100 << "%" << endl;
            output << "total write miss rate : " << (static_cast<double>(l2->writeMiss) / writeAccess) * 100 << "%" << endl;
        }
    }

    output.close();
    
    // 동적할당 된거 해제
    delete l1;
    delete l2;

    return 0;
}