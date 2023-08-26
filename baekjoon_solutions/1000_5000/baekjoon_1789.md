# baekjoon_1789

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        long s = long.Parse(Console.ReadLine());
        long i = 0, sum = 0;
        while (sum <= s)
        {
            i++;
            sum += i;
            if(sum > s) { break; }
        }
        Console.WriteLine(i - 1);
    }
}
```
