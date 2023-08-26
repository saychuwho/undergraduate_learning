# baekjoon_10807

## C++ Solution

```c++
#include <iostream>

int main() {
    int n = 0, target_num = 0, counter = 0;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cin >> target_num;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target_num) {
            counter += 1;
        }
    }
    std::cout << counter;
    delete[] arr;
}
```
