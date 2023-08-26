# baekjoon_10926

## problem

### input and output example

joonas >> joonas??!
baekjoon >> baekjoon??!

## Idea

Get string from console and add "??!" to that string. Print the string.

## C++ Solution

```c++
#include <iostream>
#include <string>

int main() {
    std::string joonas = "";
    std::cin >> joonas;
    std::cout << joonas + "??!";
}
```
