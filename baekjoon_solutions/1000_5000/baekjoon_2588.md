# baekjoon_2588

## C++ Solution

```c++
#include <iostream>

int main() {
    int a{ 0 }, b{ 0 }, b1{ 0 }, b2{ 0 }, b3{ 0 };
    std::cin >> a;
    std::cin >> b;
    b1 = b / 100;
    b2 = (b % 100) / 10;
    b3 = b % 10;
    std::cout << a * b3 << std::endl;
    std::cout << a * b2 << std::endl;
    std::cout << a * b1 << std::endl;
    std::cout << a * b << std::endl;
}
```

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int a = int.Parse(Console.ReadLine());
        int b = int.Parse(Console.ReadLine());
        int b_100 = b / 100;
        int b_10 = (b % 100) / 10;
        int b_1 = b % 10;
        Console.WriteLine(a * b_1);
        Console.WriteLine(a * b_10);
        Console.WriteLine(a * b_100);
        Console.WriteLine(a * b);
    }
}
```
