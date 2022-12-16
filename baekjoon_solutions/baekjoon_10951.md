# baekjoon_10951

## Idea

you need to use EOF(End Of File).

EOF means there are nothing to read. In C++, when you get inputs from std::cin, if there are EOF, std::cin.eof() returns ture.

In the console, you need to input EOF manually with Ctrl + Z(windows) or Ctrl+d(Unix).

## C++ Solution

```c++
#include <iostream>

int main() {
    int i = 0;
    while (true) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        if (std::cin.eof() == true) {
            break;
        }
        std::cout << a + b << std::endl;
    }
}
```
