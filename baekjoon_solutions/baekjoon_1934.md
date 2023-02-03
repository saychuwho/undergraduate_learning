# baekjoon_1934

## C# Solution

```c#
using System;

class HelloWorld
{
    static int Func1(int a, int b)
    {
        int i = 1, result = 0;
        while (true)
        {
            result = a * i;
            if(result%b == 0) { break; }
            i++;
        }
        return result;
    }
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        for(int i = 0; i < n; i++)
        {
            int[] get_num = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            Console.WriteLine(Func1(get_num[0], get_num[1]));
        }
    }
}
```
