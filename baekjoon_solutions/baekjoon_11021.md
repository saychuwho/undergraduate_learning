# baekjoon_11021

## C++ Solution

```c++
#include <iostream>

int main() {
    int testcasenum = 0;
    std::cin >> testcasenum;
    for (int i = 1; i <= testcasenum; i++) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        std::cout << "Case #" << i << ": " << a + b << "\n";
    }
}
```
