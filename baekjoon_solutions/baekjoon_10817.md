# baekjoon_10817

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] get_num = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Array.Sort(get_num);
        Console.WriteLine(get_num[1]);
    }
}
```
