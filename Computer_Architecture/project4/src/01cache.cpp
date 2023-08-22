#include "01cache.h"
#include "../include/03datamanage.h"

#include <random>
#include <bitset>
#include <iostream>


Block::Block(string startAddr, unsigned long timestep){
    block_start_addr = startAddr;
    valid_bit = 1;
    accessedTime = timestep;
}

Block::Block(){
    block_start_addr = "000000000000000000000000000000000000000000000000";
    valid_bit = 0;
    dirty_bit = 2;
    isEmpty = true;
}

unsigned int Cache::power_2(unsigned int num){
    unsigned int retNum = 0;
    unsigned int tempNum = num;
    while(tempNum != 1){
        tempNum = tempNum / 2;
        retNum++;
    }
    return retNum;
}

// retVector의 첫번째 요소가 tag, 두번째 요소가 index
// bit string 형태로 들어올거니까 그대로 처리하면 됨. 이때, block_size대로는 이미 처리가 완료됨.
vector<unsigned long> Cache::get_tag(string memaddr){
    if(DEBUG_2) cout << "Cache::get_tag" << endl;
    unsigned long tag = stoul(memaddr.substr(0, memaddr.length() - power_2(set_num)), nullptr, 2);
    unsigned long index = stoul(memaddr.substr(memaddr.length() - power_2(set_num), power_2(set_num)), nullptr, 2);
    vector<unsigned long> retVector = {tag, index};
    return retVector;
}

vector<unsigned long> Cache::get_tag_realMem(string memaddr){
    if(DEBUG_2) cout << "Cache::get_tag_realMem" << endl;
    if(DEBUG) cout << memaddr << endl;

    unsigned long tempMemAddr = 0;
    if(StrHaveChar(memaddr, 'x')){
        if(DEBUG) cout << "this is HEX" << endl;
        tempMemAddr = stoul(memaddr, nullptr, 16);
    }
    else{
        if(DEBUG) cout << "this is binary" << endl;
        tempMemAddr = stoul(memaddr, nullptr, 2);
    }
    bitset<48> memAddr(tempMemAddr);
    string memAddr_bitString = memAddr.to_string();
    if(DEBUG) cout << tempMemAddr << endl;
    if(DEBUG) cout << memAddr_bitString << endl;
    unsigned long tag = stoul(memAddr_bitString.substr(0, 48 - power_2(set_num) - power_2(block_size)), nullptr, 2);
    unsigned long index = stoul(memAddr_bitString.substr(48 - power_2(set_num) - power_2(block_size), power_2(set_num)), nullptr, 2);
    vector<unsigned long> retVector = {tag, index};
    return retVector;
}

unsigned int Cache::get_vars(string var){
    if(var == "readHit")
        return readHit;
    else if(var == "readMiss")
        return readMiss;
    else if(var == "writeHit")
        return writeHit;
    else if(var == "writeMiss")
        return writeMiss;
    else if(var == "cleanEviction")
        return  cleanEviction;
    else if(var == "dirtyEviction")
        return dirtyEviction;
    else if(var == "block_size")
        return block_size;
    else if(var == "asso_way")
        return asso_way;
    else if(var == "cache_size")
        return cache_size;
    else if(var == "total_block_num")
        return total_block_num;
    else if(var == "set_num")
        return set_num;
    else
        return 0;
}

Block* Cache::access_addr(vector<string> meminfo){
    if(DEBUG) cout << "--->" <<  this->whatCache << " access_addr" << endl;

    vector<unsigned long> memTagIndex = get_tag_realMem(meminfo.at(1));
    bool isHit = false;
    Block* accessBlock;

    // debug
    if(DEBUG){
        cout << endl;
        cout << this->whatCache << endl;
        cout << "mem addr " << meminfo.at(1) << endl;
        cout << "tag : " << memTagIndex.at(0) << endl;
        cout << "index : " << memTagIndex.at(1) << endl;
    }

    // hit, miss 여부를 판단.
    if(DEBUG) cout << endl << "Is it hit or miss?" << endl;

    for(vector<Block*>::iterator i=cache.at(memTagIndex.at(1)).begin(); i != cache.at(memTagIndex.at(1)).end(); i++){
        // cache 별로 set 개수가 다르니, 이를 반영해서 cache별로 계산을 해야 한다.
        vector<unsigned long> blockTagIndex = get_tag((*i)->block_start_addr);
        if(DEBUG) cout << blockTagIndex.at(0) << endl;
        if(DEBUG) cout << memTagIndex.at(0) << endl << endl;
        if(blockTagIndex.at(0) == memTagIndex.at(0)){
            isHit = true;
            accessBlock = (*i);
            break;
        }
    }
    // hit인 경우
    if(isHit){
        // timestep으로 저장하자.
        if(DEBUG) cout << "write timestep to block" << endl;
        accessBlock->accessedTime = totalAccess;
        if(DEBUG) cout << meminfo.at(0) << endl;
        // read 인 경우와 write인 경우 해야할 행동들을 하자.
        if(meminfo.at(0) == "R"){
            readHit++;
            if(DEBUG) cout << "read hit" << endl;
        }
        else{
            accessBlock->dirty_bit = 1;
            writeHit++;
            if(DEBUG) cout << "write hit" << endl;
        }
    }
    // miss인 경우 : block을 새로 저장해야 한다. 그래야 자동으로 저장이 되지.
    else{
        // miss_handler로부터 새로운 block을 받아온다.
        if(DEBUG) cout << "send to miss handler" << endl;
        accessBlock = miss_handler(meminfo);
        if(DEBUG) cout << "miss handler returned this : " << accessBlock->block_start_addr << endl;
        // 그 후 새로운 block을 해당하는 set에 집어넣는다.
        if(DEBUG) cout << "put new block to cache" << endl;
        add_block(accessBlock);
        // timestep으로 저장하자.
        if(DEBUG) cout << "write timestep to block" << endl;
        accessBlock->accessedTime = totalAccess;
        // read인 경우와 write인 경우 해야 할 행동을 하자.
        if(meminfo.at(0) == "R"){
            readMiss++;
            if(DEBUG_2) cout << "read miss" << endl;
            if(DEBUG) cout << "read miss" << endl;
        }
        else if(meminfo.at(0) == "W"){
            accessBlock->dirty_bit = 1;
            writeMiss++;
            if(DEBUG_2) cout << "write miss" << endl;
            if(DEBUG) cout << "write miss" << endl;
        }
    }
    // 반환하는 거는 해당하는 정보만 가진 copy본을 return해야 한다.
    Block* ret_block = new Block(*accessBlock);
    if(DEBUG) cout << "returned ret_block" << endl;
    if(DEBUG) cout << endl;
    return ret_block;
}

L1Cache::L1Cache(unsigned int capacity, unsigned int asso, unsigned int blockSize, unsigned int isLRU, Block* emptyblock){
    // init 할 변수들부터 init한다.
    cache_size = capacity;
    asso_way = asso;
    block_size = blockSize;
    whatCache = "L1 Cache";
    if(isLRU == 2) is_lru = false;

    emptyBlock = emptyblock;
    
    // cache 속 전체 block의 개수를 구하자 우선
    total_block_num = (cache_size * 1024) / block_size;
    // set의 개수를 구하자.
    set_num = total_block_num / asso_way;
    // cache 속 내용물들을 빈 Block으로 동적할당해서 초기화하자.
    for(unsigned int i=0;i<set_num;i++){
        vector<Block*> tempVector;
        for(unsigned int j=0;j<asso_way;j++){
            // Block* empty_block = new Block();
            // tempVector.push_back(empty_block);
            tempVector.push_back(emptyBlock);
        }
        cache.push_back(tempVector);
    }

    // debug
    if(DEBUG){
        cout << endl;
        cout << this->whatCache << endl;
        cout << "set num : " << this->set_num << endl;
        cout << "block size : " << this->block_size << endl;
        cout << "asso way : " << this->asso_way << endl;
        cout << "cache size : " << this->cache_size << endl;
    }
}

L1Cache::~L1Cache(){
    // 동적할당 된 것들을 모두 해제해주어야 한다.
    for(unsigned int i=0;i<set_num;i++){
        for(unsigned int j=0;j<asso_way;j++){
            delete cache.at(i).at(j);
        }
    }
}

void L1Cache::init_cache_pointer(Cache* cache){ 
    L2 = cache;
}

Block* L1Cache::miss_handler(vector<string> meminfo){
    return L2->access_addr(meminfo);
}

// block을 받아와서 해당하는 set에 집어넣어야 한다.
void L1Cache::add_block(Block* block){
    vector<unsigned long> blockTagIndex = get_tag(block->block_start_addr);
    if(DEBUG) cout << ">> blockTagIndex tag : " << blockTagIndex.at(0) << endl;
    // 만약에 빈 block이 있다면, 처음으로 빈 block에 집어넣자.
    bool isDone = false;
    for(vector<Block*>::iterator i=cache.at(blockTagIndex.at(1)).begin(); i != cache.at(blockTagIndex.at(1)).end();i++){
        if((*i)->isEmpty){
            if(DEBUG) cout << "delete the dummy in the empty way" << endl;
            // delete (*i);
            (*i) = block;
            isDone = true;
            if(DEBUG) cout << "added new block to empty way" << endl;
            break;
        }
    }
    // 빈 block이 없다면, evict해야 한다.
    if(!isDone){
        if(DEBUG) cout << "send to evict handler" << endl;
        evict_block(blockTagIndex, block->block_start_addr);
        add_block(block);
    }
    if(DEBUG) cout << "end adding the block" << endl;
}


void L1Cache::evict_block(vector<unsigned long> tagindex, string start_addr){
    if(DEBUG) cout << "L1 evict called" << endl;
    
    // 새로운 위치를 is_lru일때와 아닐때로 나누어서 구해놓자.
    long newLoc = -1;

    // startaddr이 있는가? 원래 evict 같으면 진작에 없어야 하니까 isBlockExist가 false여야 하고, 
    // 있으면 있는 block을 내쫒는 상황이니 그 block만 내쫒아야 한다.
    bool isBlockExist = false;
    
    // 있는 tag를 내쫒으려 하는게 아니라, 원래는 아무나 일단 내쫒아야 하는데, 표적이 되는 tag가 있다면, 걔를 내쫒아야 한다.
    if(DEBUG) cout << "is really tag have the block? TEST it" << endl;

    vector<unsigned long> Temp_Tag2 = get_tag(start_addr);
    for(unsigned int i=0; i < asso_way;i++){
        if(DEBUG) cout << "is it here?" << endl;
        vector<unsigned long> tempTag = get_tag(cache.at(Temp_Tag2.at(1)).at(i)->block_start_addr);
        if(DEBUG) cout << "is it here?" << endl;
        if(tempTag.at(0) == Temp_Tag2.at(0)){ // 해당하는 tag가 실제로 있다는 소리이니 그거만 new loc를 하면 된다.
            isBlockExist = true;
            newLoc = i;
            isBlockExist = true;
            break;
        }
    }
    if(DEBUG) cout << "is it here?" << endl;
    if(!isBlockExist && tagindex.size() == 2){
        // lru를 사용할 때 그냥 무식한 방법으로 짜봅시다.
        if(this->is_lru){
            if(DEBUG) cout << "LRU" << endl;
            map<unsigned long, unsigned long> tempLRU;
            for(unsigned long long i=0;i < cache.at(tagindex.at(1)).size();i++){
                tempLRU[cache.at(tagindex.at(1)).at(i)->accessedTime] = i;
            }
            newLoc = tempLRU.begin()->second;
        }
        // random 일 때
        else{
            if(DEBUG) cout << "RANDOM" << endl;
            // 난수 생성을 위한 시드 초기화
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(0, cache.at(tagindex.at(1)).size()-1);
            // 생성된 난수 위치 중 하나를 delete하고 새로 할당
            newLoc = dis(gen);
        }
    }

    if(newLoc != -1){
        // evict 될 Block의 주소
        Block* evictBlock = cache.at(Temp_Tag2.at(1)).at(newLoc);
        // if(DEBUG) cout << "evictblock's tag : " << get_tag(evictBlock->block_start_addr).at(0) << endl;
        
        // old code
        // if(DEBUG) cout << "newblock's tag : " << get_tag(to_string(nBlock->block_start_addr)).at(0) << endl;
        
        // clean evict와 dirty evict를 나누자.
        // clean
        if(evictBlock->dirty_bit == 0){
            if(DEBUG) cout << "clean eviction" << endl;
            cleanEviction++;
        }
        // dirty
        else if(evictBlock->dirty_bit==1){
            if(DEBUG) cout << "dirty eviction" << endl;
            dirtyEviction++;
            // L1에서 일어난 dirty eviction일 경우에는 L2에 write를 해야 한다.
            unsigned long evictBlockRealaddr = stoul(evictBlock->block_start_addr, nullptr, 2) << power_2(block_size);
            bitset<48> evictBlockRealaddr_bitset(evictBlockRealaddr);
            vector<string> tempMeminfo = {"W", evictBlockRealaddr_bitset.to_string()};
            Block* dummy = L2->access_addr(tempMeminfo);
        }
        // 모든 전처리가 끝난 후, 원래 block을 빈 block으로 교체하자.
        //delete evictBlock;
        // evictBlock = new Block();
        if(!evictBlock->isEmpty){
            if(DEBUG) cout << "deleting non empty block" << endl;
            delete evictBlock;
        }
        if(DEBUG) cout << "give new block init" << endl;
        cache.at(Temp_Tag2.at(1)).at(newLoc) = emptyBlock;
        
    }

}

L2Cache::L2Cache(unsigned int capacity, unsigned int asso, unsigned int blockSize, unsigned int isLRU, Block* emptyblock){
    // init 할 변수들부터 init한다.
    cache_size = capacity;
    asso_way = asso;
    block_size = blockSize;
    whatCache = "L2 Cache";
    if(isLRU == 2) is_lru = false;

    if(DEBUG) cout << "L2 Cache constructor" << endl;

    emptyBlock = emptyblock;

    // cache 속 전체 block의 개수를 구하자 우선
    total_block_num = (cache_size * 1024) / block_size;
    // set의 개수를 구하자.
    set_num = total_block_num / asso_way;
    // cache 속 내용물들을 빈 Block으로 동적할당해서 초기화하자.
    // cache 속 내용물들을 빈 Block으로 동적할당해서 초기화하자.
    for(unsigned int i=0;i<set_num;i++){
        vector<Block*> tempVector;
        for(unsigned int j=0;j<asso_way;j++){
            //Block* empty_block = new Block();
            //tempVector.push_back(empty_block);
            tempVector.push_back(emptyBlock);
        }
        cache.push_back(tempVector);
    }

    // debug
    if(DEBUG){
        cout << this->whatCache << endl;
        cout << "set num : " << this->set_num << endl;
        cout << "block size : " << this->block_size << endl;
        cout << "asso way : " << this->asso_way << endl;
        cout << "cache size : " << this->cache_size << endl;
    }
}

L2Cache::~L2Cache(){
    // 동적할당 된 것들을 모두 해제해주어야 한다.
    for(unsigned int i=0;i<set_num;i++){
        for(unsigned int j=0;j<asso_way;j++){
            delete cache.at(i).at(j);
        }
    }
}

void L2Cache::init_cache_pointer(Cache* cache){
    L1 = cache;
}

// L2에서 miss가 발생했을 시 : 메모리에서 해당하는 block을 들고오는거를 표현해야 한다.
Block* L2Cache::miss_handler(vector<string> meminfo){
    if(DEBUG_2) cout << "L2Cache::miss_handler" << endl;

    unsigned long tempMemaddr = stoul(meminfo.at(1), nullptr, 16);
    bitset<48> tempMemaddr_bitset(tempMemaddr);
    string tempMemaddr_string = tempMemaddr_bitset.to_string().substr(0, 48 - power_2(block_size));
    Block* ret_block = new Block(tempMemaddr_string, totalAccess);
    return ret_block;
}

void L2Cache::add_block(Block* block){
    if(DEBUG) cout << "L2 add block called" << endl;
    vector<unsigned long> blockTagIndex = get_tag(block->block_start_addr);
    // 만약에 빈 block이 있다면, 처음으로 빈 block에 집어넣자.
    bool isDone = false;
    for(vector<Block*>::iterator i=cache.at(blockTagIndex.at(1)).begin(); i != cache.at(blockTagIndex.at(1)).end();i++){
        if((*i)->isEmpty){
            //delete (*i);
            (*i) = block;
            isDone = true;
            if(DEBUG) cout << "added new block to empty way" << endl;
            break;
        }
    }
    // 빈 block이 없다면, evict해야 한다. 
    if(!isDone){
        if(DEBUG) cout << "send to evict handler" << endl;
        evict_block(blockTagIndex, block->block_start_addr);
        add_block(block);
    }
}

void L2Cache::evict_block(vector<unsigned long> tagindex, string start_addr){
    // 새로운 위치를 is_lru일때와 아닐때로 나누어서 구해놓자.
    unsigned long newLoc = 0;
    // lru를 사용할 때 그냥 무식한 방법으로 짜봅시다.
    if(this->is_lru){
        if(DEBUG) cout << "LRU" << endl;
        map<unsigned long, unsigned long> tempLRU;
        for(unsigned long i=0;i < cache.at(tagindex.at(1)).size();i++){
            tempLRU[cache.at(tagindex.at(1)).at(i)->accessedTime] = i;
        }
        newLoc = tempLRU.begin()->second;
        if(DEBUG) cout << tempLRU.begin()->first << endl;
        if(DEBUG) cout << tempLRU.begin()->second << endl;
    }
    // random 일 때
    else{
        if(DEBUG) cout << "RANDOM" << endl;
        // 난수 생성을 위한 시드 초기화
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, cache.at(tagindex.at(1)).size()-1);
        // 생성된 난수 위치 중 하나를 delete하고 새로 할당
        newLoc = dis(gen);
    }

    // evict 될 Block의 주소
    Block* evictBlock = cache.at(tagindex.at(1)).at(newLoc);
    
    // if(DEBUG) cout << "evictblock's tag : " << get_tag(evictBlock->block_start_addr).at(0) << endl;


    // old code
    // if(DEBUG) cout << "newblock's tag : " << get_tag(to_string(nBlock->block_start_addr)).at(0) << endl;
    
    // 만약에 L1에도 동일한 block이 있다면, L1에서도 이를 evict해야 한다.
    if(DEBUG) cout << "check if L1 has the same block" << endl;
    // tagindex에 하나를 더 넣어서 보내자.
    vector<unsigned long> temp_tagindex = tagindex;
    temp_tagindex.push_back(1);
    L1->evict_block(temp_tagindex, evictBlock->block_start_addr);

    // clean evict와 dirty evict를 나누자.
    // clean
    if(evictBlock->dirty_bit == 0){
        if(DEBUG) cout << "clean eviction" << endl;
        cleanEviction++;
    }
    // dirty
    else if(evictBlock->dirty_bit != 0){
        if(DEBUG) cout << "dirty eviction" << endl;
        dirtyEviction++;
    }
    // 모든 전처리가 끝난 후, 원래 block을 빈 block으로 교체하자.
    //delete evictBlock;
    //evictBlock = new Block();
    if(!evictBlock->isEmpty){
        delete evictBlock;
    }
    cache.at(tagindex.at(1)).at(newLoc) = emptyBlock;
}