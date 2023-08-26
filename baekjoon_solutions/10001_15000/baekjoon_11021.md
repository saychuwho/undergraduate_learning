# baekjoon_11021

## C++ Solution

```c++
#include <iostream>

int main() {
    int testcasenum = 0;
    std::cin >> testcasenum;
    for (int i = 1; i <= testcasenum; i++) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        std::cout << "Case #" << i << ": " << a + b << "\n";
    }
}
```

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        for (int i = 0; i < n; i++)
        {
            int[] getnum = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            Console.WriteLine($"Case #{i+1}: {getnum[0] + getnum[1]}");
        }
    }
}
```
