# baekjoon_10156

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] get_num = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        int result = get_num[0] * get_num[1] - get_num[2];
        if (result < 0) { Console.WriteLine(0); }
        else { Console.WriteLine(result); }
    }
}
```
