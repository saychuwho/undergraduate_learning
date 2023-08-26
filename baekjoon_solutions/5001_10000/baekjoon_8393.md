# baekjoon_8393

## C++ Solution

```c++
#include <iostream>

int main() {
    int n = 0, result = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        result += i;
    }
    std::cout << result;
}
```
