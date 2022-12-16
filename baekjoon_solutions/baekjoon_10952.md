# baekjoon_10952

## C++ Solution

```c++
#include <iostream>

int main() {
    while (true) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        if (a == 0 and b == 0)
            break;
        std::cout << a + b << std::endl;
    }
}
```
