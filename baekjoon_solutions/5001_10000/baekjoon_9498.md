# baekjoon_9498

## C++ Solution

```c++
#include <iostream>

int main() {
    int score = 0;
    std::cin >> score;

    if (100 >= score and score >= 90) {
        std::cout << "A";
    }
    else if (90 > score and score >= 80) {
        std::cout << "B";
    }
    else if (80 > score and score >= 70) {
        std::cout << "C";
    }
    else if (70 > score and score >= 60) {
        std::cout << "D";
    }
    else {
        std::cout << "F";
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
        int score = int.Parse(Console.ReadLine());
        if(score >= 90) { Console.WriteLine("A"); }
        else if(score >= 80 && score <= 89) { Console.WriteLine("B"); }
        else if(score >= 70 && score <= 79) { Console.WriteLine("C"); }
        else if(score >= 60 && score <= 69) { Console.WriteLine("D"); }
        else { Console.WriteLine("F"); }
    }
}
```
