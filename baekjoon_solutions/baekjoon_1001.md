# baekjoon_1001

## Problem

Get two integer A, B and print the substract of A, B. (0 < A, B < 10)

## Idea  

Get two integer A, B with console input and print the substract with console output.

## C++ Solution

```c++
#include <iostream>

int main() {
    int a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << a - b;
}
```

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        string[] getnum = Console.ReadLine().Split();
        Console.WriteLine(Int32.Parse(getnum[0]) - Int32.Parse(getnum[1]));
    }
}
```
