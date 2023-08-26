# baekjoon_2914

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] getnum = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Console.WriteLine((getnum[1] - 1) * getnum[0] + 1);
    }
}
```
