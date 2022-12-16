# baekjoon_1330

## C++ Solution

```c++
#include <iostream>

int main() {
    int a{ 0 }, b{ 0 };
    std::cin >> a >> b;
    if (a > b) {
        std::cout << ">";
    }
    else if (a == b) {
        std::cout << "==";
    }
    else {
        std::cout << "<";
    }
}
```
