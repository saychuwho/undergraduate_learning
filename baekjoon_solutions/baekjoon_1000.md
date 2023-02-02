# baekjoon_1000

## Problem

Get two integer A, B and print the sum of A, B. (0 < A, B < 10)

## Idea  

Get two integer with console input and print it with console output.

## C++ Solution

```c++
#include <iostream>

int main() {
    int a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << a + b;
}
```

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        // C#에서 console 입력은 파이썬과 유사하다.
        string[] getnum = Console.ReadLine().Split();
        Console.WriteLine(Int32.Parse(getnum[0])+Int32.Parse(getnum[1]));
    }
}
```
