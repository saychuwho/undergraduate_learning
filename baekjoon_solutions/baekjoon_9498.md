# baekjoon_9498

## C++ Solution

```c++
#include <iostream>

int main() {
    int score = 0;
    std::cin >> score;

    if (100 >= score and score >= 90) {
        std::cout << "A";
    }
    else if (90 > score and score >= 80) {
        std::cout << "B";
    }
    else if (80 > score and score >= 70) {
        std::cout << "C";
    }
    else if (70 > score and score >= 60) {
        std::cout << "D";
    }
    else {
        std::cout << "F";
    }
}
```
