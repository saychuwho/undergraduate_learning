# baekjoon_2480

## C++ Solution

```c++
#include <iostream>

int main() {
    int a = 0, b = 0, c = 0, prise = 0;
    std::cin >> a >> b >> c;

    if (a == b or a == c or b == c) {
        if (a == b and a == c) {
            prise = 10000 + a * 1000;
        }
        else {
            if (a == b or a==c) {
                prise = 1000 + a * 100;
            }
            else {
                prise = 1000 + b * 100;
            }
        }
    }
    else {
        if (a > b and a > c) {
            prise = a * 100;
        }
        else if (b > a and b > c) {
            prise = b * 100;
        }
        else {
            prise = c * 100;
        }
    }
    std::cout << prise;
}
```
