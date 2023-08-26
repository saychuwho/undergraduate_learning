# baekjoon_2439

## C++ Solution

```c++
#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (n - i); j++) {
            std::cout << " ";
        }
        for (int k = 0; k < i; k++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}
```
