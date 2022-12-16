# baekjoon_18108

## problem

Change the Buddhist calendar to Christian Era

### input

```c++
2541
```

### output

```c++
1998
```

## Idea  

Get Buddhist calendar year and minus 543

## C++ Solution

```c++
#include <iostream>

int main() {
    int B_year = 0;
    std::cin >> B_year;
    std::cout << B_year - 543;
}
```
