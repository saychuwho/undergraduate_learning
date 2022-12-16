# baekjoon_15596

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;

long long sum(vector<int>& a) {
    long long result_num = 0;
    for (int i = 0; i < a.size(); i++) {
        result_num += a.at(i);
    }
    return result_num;
}
```
