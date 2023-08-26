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

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] start_time = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        int cooking_time = int.Parse(Console.ReadLine());
        int end_hour = 0, end_minute = 0;
        end_hour = start_time[0] + (cooking_time / 60) + ((start_time[1] + (cooking_time % 60)) / 60);
        if (end_hour >= 24)
        {
            end_hour -= 24;
        }
        end_minute = (start_time[1] + (cooking_time % 60)) % 60;
        Console.WriteLine($"{end_hour} {end_minute}");
    }
}
```
