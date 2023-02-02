# baekjoon_3046

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] getnum = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Console.WriteLine(2*getnum[1]-getnum[0]);
    }
}
```
