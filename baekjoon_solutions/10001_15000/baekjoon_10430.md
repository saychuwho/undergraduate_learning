# baekjoon_10430

## Problem

Is (A+B)%C equals to ((A%C) + (B%C))%C?

Is (AXB)%C equals to ((A%C) X (B%C))%C?

Calculate these.

## Ideas  

Get three numbers from console and calculate (A+B)%C, ((A%C) + (B%C))%C, (AXB)%C and ((A%C) X (B%C))%C

## C++ Solution

```c++
#include <iostream>

int main() {
    int a{ 0 }, b{ 0 }, c{ 0 };
    std::cin >> a >> b >> c;
    std::cout << (a + b) % c << std::endl;
    std::cout << ((a % c) + (b % c)) % c << std::endl;
    std::cout << (a * b) % c << std::endl;
    std::cout << ((a % c) * (b % c)) % c << std::endl;
}
```

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int[] getnum = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Console.WriteLine((getnum[0] + getnum[1]) % getnum[2]);
        Console.WriteLine( ((getnum[0] % getnum[2]) + (getnum[1] % getnum[2])) % getnum[2] );
        Console.WriteLine((getnum[0]*getnum[1]) % getnum[2]);
        Console.WriteLine(((getnum[0] % getnum[2]) * (getnum[1] % getnum[2])) % getnum[2]);
    }
}
```
