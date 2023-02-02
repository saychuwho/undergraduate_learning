# baekjoon_5355

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        for(int i = 0; i < n; i++)
        {
            string[] get_info = Console.ReadLine().Split(' ');
            double result = double.Parse(get_info[0]);
            for(int j = 1; j < get_info.Length; j++)
            {
                if(get_info[j] == "@") { result *= 3; }
                else if(get_info[j] == "%") { result += 5; }
                else { result -= 7; }
            }
            Console.WriteLine(string.Format("{0:0.00}", result));
        }
    }
}
```
