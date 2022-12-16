# baekjoon_10871

## C++ Solution

```c++
#include <iostream>

int main() {
    int n = 0, x = 0;
    std::cin >> n >> x;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] < x) {
            std::cout << arr[i] << " ";
        }
    }
    delete[] arr;
}
```
