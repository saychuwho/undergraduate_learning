# baekjoon_2753

## C++ Solution

```c++
#include <iostream>

int main() {
    int year = 0;
    std::cin >> year;

    if (year % 400 == 0) {
        std::cout << 1;
    }
    else if (year % 4 == 0 and year % 100 != 0) {
        std::cout << 1;
    }
    else {
        std::cout << 0;
    }
}
```
