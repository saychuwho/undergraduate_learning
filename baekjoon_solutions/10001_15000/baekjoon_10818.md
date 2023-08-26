# baekjoon_10818

## C++ Solution

```c++
#include <iostream>
#include <algorithm>

int main() {
    int n = 0;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::sort(arr, arr + n);
    std::cout << arr[0] << " " << arr[n-1];
}
```
