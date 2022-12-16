# baekjoon_2525

## C++ Solution

```c++
#include <iostream>

int main() {
    int hour = 0, minute = 0, cook_time = 0, result_hour = 0, result_minute = 0;
    std::cin >> hour >> minute;
    std::cin >> cook_time;

    result_hour = hour + (cook_time / 60);
    result_minute = minute + (cook_time % 60);
    if (result_minute >= 60) {
        result_minute -= 60;
        result_hour += 1;
    }
    if (result_hour >= 24) {
        result_hour -= 24;
    }
    std::cout << result_hour << " " << result_minute;
}
```
