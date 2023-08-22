#ifndef CACHE
#define CACHE

#include <map>
#include <string>
#include <vector>

using namespace std;

extern unsigned long totalAccess;
extern unsigned long readAccess;
extern unsigned long writeAccess;

extern bool DEBUG;
extern bool DEBUG_2;

// Block의 역할을 하는 class
class Block{
public:
    // dirty_bit, valid_bit을 나타내는 부분
    // dirty bit가 1이면 dirty, 0이면 clean
    unsigned int dirty_bit = 0;
    // valid_bit이 1이면 내용물이 있다는 뜻이고, 0이면 내용물이 없다는 뜻이다.
    unsigned int valid_bit = 0;
    
    // bit 형식의 string이 들어가있어야 한다.
    string block_start_addr = "";
    // 실제 데이터가 들어갈 필요는 없다.

    // timestep으로 lru를 구현하자 그냥
    unsigned long accessedTime = 0;

    bool isEmpty = false;

    // constructor : block_size와 block_start_addr를 받아서 block map을 초기화 한다.
    Block(string startAddr, unsigned long timestep);
    // constructor : 빈 Block을 생성하는 constructor이다.
    Block();
};

// Cache의 역할을 하는 class
class Cache{
public:
    // 각 cache의 hit, miss 여부, clean dirty eviction 여부를 나타냄
    unsigned int readHit = 0;
    unsigned int readMiss = 0;
    unsigned int writeHit = 0;
    unsigned int writeMiss = 0;
    unsigned int cleanEviction = 0;
    unsigned int dirtyEviction = 0;
    // cache의 block size를 나타냄
    unsigned int block_size = 0;
    // associative를 나타냄. 기본값으로 1을 주자.
    unsigned int asso_way = 1;
    // cache의 size를 나타냄 : KB 단위로 저장하자.
    unsigned int cache_size = 0;
    // 전체 block의 개수는?
    unsigned int total_block_num = 0;
    // cache 속 set의 개수는?
    unsigned int set_num = 0;
    // block evict policy로 lru(true)를 사용할 것인가, random(false)를 사용할 것인가
    bool is_lru = true;
    // 실제로 block들을 담는 공간과, lru를 지원하기 위한 vector 비스무리한 거는 동적할당으로 해둬야 메모리가 터지지 않겠지?
    vector<vector<Block*>> cache;
    // debug 목적으로 무슨 cache 인지를 파악하기 위한 변수
    string whatCache;

    Block* emptyBlock;

    // constructor : 상속받는 곳에서 각자 constructor를 정의해두어야 한다.
    // 2의 몇승인지를 구해야 한다.
    unsigned int power_2(unsigned int num);
    // test file 속에 있는 주소를 string 형태로 받은 후, 여기서 block offset, tag, index로 변환해 이를 모두 담은 vector를 반환
    vector<unsigned long> get_tag(string memaddr);
    // 실제 주소에서 tag를 들고올 때는 이전대로 해야 한다.
    vector<unsigned long> get_tag_realMem(string memaddr);
    // block size, miss 등은 공통적으로 가지고 있으니까 이것들을 출력하는 함수는 공통적으로 만들어도 될 듯.
    unsigned int get_vars(string var);
    // 서로가 참조해야 하는 cache의 pointer를 init하는 함수
    virtual void init_cache_pointer(Cache* cache) = 0;
    // 데이터에 access하는 부분 : L1일 경우에는 miss가 났을 시 L2에서 받아와야 하고, L2의 경우에는 miss가 발생시 블록을 load 한 이후 L1에게도 보내야 한다.
    // main 함수에서 vector<string> 형태로 명령을 받으므로, 그거 통째로 받아서 처리하자.
    // 근데 miss handler가 이거를 담당하게 만들어놔서, virtual로 안해도 될 듯.
    // 유연성을 위해서 Block* 을 반환하자.
    Block* access_addr(vector<string> meminfo);
    // miss시 block을 불러오는 부분. 각 cache 별로 다르게 처리되어야 한다.
    virtual Block* miss_handler(vector<string> meminfo) = 0;
    // 각각 cache에서 evict를 할 때 내세워야 할 방법이 다르므로 virtual로 정의해둔다.
    // setNum을 받기보다는, Block 자체를 받아오자.
    virtual void add_block(Block* block) = 0;
    // evict를 내가 따로 놔둔 이유가 있었구먼....
    virtual void evict_block(vector<unsigned long> tagindex, string start_addr) = 0;
};

class L1Cache : public Cache{
private:
    // L2 cache의 주소를 알아야 하니 미리 정의
    Cache* L2;
public:
    L1Cache(unsigned int capacity, unsigned int asso, unsigned int blockSize, unsigned int isLRU, Block* emptyblock);
    ~L1Cache();
    // l2 cache의 pointer를 init하는 함수
    void init_cache_pointer(Cache* cache);
    // L1 cache에서 miss_handler
    Block* miss_handler(vector<string> meminfo);
    // L1 cache에서 evict 해야 하는 부분 : 그냥 evict하면 된다.
    void add_block(Block* block);
    // L1에서 evict
    void evict_block(vector<unsigned long> tagindex, string start_addr);
};

class L2Cache : public Cache{
private:
    // L1 cache의 주소를 알아야 하니 미리 정의
    Cache* L1;
public:
    L2Cache(unsigned int capacity, unsigned int asso, unsigned int blockSize, unsigned int isLRU, Block* emptyblock);
    ~L2Cache();
    // l1 cache의 pointer를 init하는 함수
    void init_cache_pointer(Cache* cache);
    // L2 cache에서 miss_handler
    Block* miss_handler(vector<string> meminfo);
    // L2 cache에서 evict 해야 하는 부분
    void add_block(Block* block);
    // L2에서 evict
    void evict_block(vector<unsigned long> tagindex, string start_addr);
};

#endif