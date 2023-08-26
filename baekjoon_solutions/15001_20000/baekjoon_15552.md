# baekjoon_15552

## C++ Solution

```c++
#include <iostream>

int main() {
    std::cin.tie(NULL);
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    int testcasenum = 0;
    std::cin >> testcasenum;
    for (int i = 0; i < testcasenum; i++) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        std::cout << a + b << "\n";
    }
}
```
