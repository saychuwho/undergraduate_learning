# baekjoon_2438

## C++ Solution

```c++
#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}
```
