# baekjoon_10039

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] scores = new int[5];
        for(int i = 0; i < 5; i++)
        {
            scores[i] = int.Parse(Console.ReadLine());
            if(scores[i] < 40) { scores[i] = 40; }
        }
        int sum = scores.Sum();
        Console.WriteLine(sum / 5);
    }
}
```
