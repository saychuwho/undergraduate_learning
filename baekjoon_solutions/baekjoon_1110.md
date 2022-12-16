# baekjoon_1110

## C++ Solution

```c++
#include <iostream>

int main() {
    int cycle = 0, init_num = 0, after_num = 0;
    std::cin >> init_num;
    after_num = init_num;
    do{
        int after_num_10 = (after_num / 10), after_num_1 = (after_num % 10);
        int temp_num = after_num_10 + after_num_1;
        after_num = (after_num_1 * 10) + temp_num%10;
        cycle++;
    } while (after_num != init_num);
    std::cout << cycle;
}
```
