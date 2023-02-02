# baekjoon_2530

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] start_time = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        int cooking_time = int.Parse(Console.ReadLine());
        int end_hour = 0, end_minute = 0, end_second = 0, end_day = 0;
        int cooking_second = cooking_time % 60, cooking_minute = (cooking_time / 60) % 60, cooking_hour = (cooking_time / 60) / 60;
        end_second = start_time[2] + cooking_second;
        end_minute = start_time[1] + cooking_minute;
        end_hour = start_time[0] + cooking_hour;
        if (end_second >= 60) { end_minute += end_second / 60;  end_second = end_second % 60; }
        if(end_minute >= 60) { end_hour += end_minute / 60;  end_minute = end_minute % 60; }
        if(end_hour >= 24) { end_day += end_hour / 24; end_hour = end_hour % 24; }
        Console.WriteLine($"{end_hour} {end_minute} {end_second}");
    }
}
```
