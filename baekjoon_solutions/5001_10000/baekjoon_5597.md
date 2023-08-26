# baekjoon_5597

## C++ Solution

Becareful not to corrupt heap memory using dynamic allocation.

```c++
#include <iostream>

int main() {
    int* attendence = new int[30];
    for (int i = 0; i < 30; i++) {
        attendence[i] = 0;
    }
    for (int i = 0; i < 28; i++) {
        int temp = 0;
        std::cin >> temp;
        attendence[temp-1] = temp;
    }
    for (int i = 0; i < 30; i++) {
        if (attendence[i] == 0) {
            std::cout << i+1 << std::endl;
        }
    }
    delete[] attendence;
}
```
