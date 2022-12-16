# baekjoon_14681

## C++ Solution

```c++
#include <iostream>

int main() {
    int x = 0, y = 0;
    std::cin >> x;
    std::cin >> y;

    if (x > 0 and y > 0) {
        std::cout << 1;
    }
    else if (x < 0 and y>0) {
        std::cout << 2;
    }
    else if (x < 0 and y < 0) {
        std::cout << 3;
    }
    else {
        std::cout << 4;
    }
}
```
