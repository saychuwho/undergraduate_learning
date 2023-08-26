# baekjoon_25304

## C++ Solution

```c++
#include <iostream>

int main() {
    int x = 0, n = 0, result_x = 0;
    std::cin >> x; std::cin >> n;
    for (int i = 0; i < n; i++) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        result_x += a * b;
    }
    if (x == result_x)
        std::cout << "Yes";
    else
        std::cout << "No";
}
```
