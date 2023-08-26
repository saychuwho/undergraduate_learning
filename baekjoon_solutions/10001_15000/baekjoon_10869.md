# baekjoon_1001

## Problem

Get two integer A, B and print the sum, substract, multiplication, share and remainder of A, B. (0 < A, B < 10)

## Idea  

Get two integer A, B with console input and print the sum, substract, multiplication, share and remainder of A, B with console output.

## C++ Solution

```c++
#include <iostream>

int main() {
    int a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a / b << std::endl;
    std::cout << a % b << std::endl;
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
        Console.WriteLine(int.Parse(getnum[0]) + int.Parse(getnum[1]));
        Console.WriteLine(int.Parse(getnum[0]) - int.Parse(getnum[1]));
        Console.WriteLine(int.Parse(getnum[0]) * int.Parse(getnum[1]));
        Console.WriteLine(int.Parse(getnum[0]) / int.Parse(getnum[1]));
        Console.WriteLine(int.Parse(getnum[0]) % int.Parse(getnum[1]));
    }
}
```
