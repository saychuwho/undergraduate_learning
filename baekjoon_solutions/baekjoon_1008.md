# baekjoon_1001

## Problem

Get two integer A, B and print the division of A, B. (0 < A, B < 10)

## Idea  

Get two integer A, B with console input and print the division of A, B with console output.

## C++ Solution

std::cout.precision() is needed to pass the judgement system. Also double type is more accurate than float type.

```c++
#include <iostream>

int main() {
    std::cout.precision(10);
    double a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << a / b;
}
```

## Python3 Solution

```python
a, b = map(int, input().split(" "))
print(a/b)
```
