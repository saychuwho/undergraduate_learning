# baekjoon_2562

## Idea

In C++, somehow std::sort() is working only with dynamically allocated arrays. I don't know why....

## C++ Solution

```c++
#include <iostream>
#include <algorithm>

int main() {
    int* arr1 = new int[9];
    int* arr2 = new int[9];
    for (int i = 0; i < 9; i++) {
        int temp = 0;
        std::cin >> temp;
        arr1[i] = temp;
        arr2[i] = temp;
    }
    std::sort(arr1, arr1 + 9);
    int index = 0;
    for (int i = 0; i < 9; i++) {
        if (arr2[i] == arr1[8]) {
            index = i;
        }
    }
    std::cout << arr1[8] << std::endl;
    std::cout << index+1;
    delete[] arr1;
    delete[] arr2;
}
```
