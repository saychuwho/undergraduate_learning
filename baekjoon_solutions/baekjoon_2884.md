# baekjoon_2884

## C++ Solution

```c++
#include <iostream>

int main() {
    int hour = 0, minute = 0, result_hour = 0, result_minute = 0;
    std::cin >> hour >> minute;

    result_hour = hour;
    result_minute = minute - 45;
    if (result_minute < 0) {
        result_minute = 60 + result_minute;
        result_hour -= 1;
    }
    if (result_hour < 0) {
        result_hour = 23;
    }
    std::cout << result_hour << " " << result_minute;
}
```
