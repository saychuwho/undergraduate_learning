# baekjoon_4101

## C# Soluiton

```c#
using System;

class HelloWorld
{
    static string Compare(int x, int y){ return (x > y) ? "Yes" : "No"; }
    static void Main(string[] args)
    {
        while (true)
        {
            int[] get_num = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            if (get_num[0] == 0 && get_num[1] == 0) { break; }
            Console.WriteLine(Compare(get_num[0], get_num[1]));
        }
    }
}
```
