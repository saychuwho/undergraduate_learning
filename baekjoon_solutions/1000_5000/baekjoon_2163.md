# baekjoon_2163

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] getnum = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Console.WriteLine(getnum[0]*getnum[1]-1);
    }
}
```
