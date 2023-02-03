# baekjoon_2480

## C++ Solution

```c++
#include <iostream>

int main() {
    int a = 0, b = 0, c = 0, prise = 0;
    std::cin >> a >> b >> c;

    if (a == b or a == c or b == c) {
        if (a == b and a == c) {
            prise = 10000 + a * 1000;
        }
        else {
            if (a == b or a==c) {
                prise = 1000 + a * 100;
            }
            else {
                prise = 1000 + b * 100;
            }
        }
    }
    else {
        if (a > b and a > c) {
            prise = a * 100;
        }
        else if (b > a and b > c) {
            prise = b * 100;
        }
        else {
            prise = c * 100;
        }
    }
    std::cout << prise;
}
```

## C# Solution
```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int score = 0;
        int[] dice_num = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Array.Sort(dice_num);
        if(dice_num[2] == dice_num[1] && dice_num[2] == dice_num[0])
        {
            score = 10000 + dice_num[2] * 1000;
        }
        else if(dice_num[2] == dice_num[1] || dice_num[2] == dice_num[0])
        {
            score = 1000 + dice_num[2] * 100;
        }
        else if (dice_num[0] == dice_num[1])
        {
            score = 1000 + dice_num[1] * 100;
        }
        else
        {
            score = dice_num[2] * 100;
        }
        Console.WriteLine(score);
    }
}
```
