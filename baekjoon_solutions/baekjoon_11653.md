# baekjoon_11653

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	long long n = 0;
	cin >> n;
	long long temp = n;
	while (temp > 1) {
		long long divided_prime = 0;
		for (long long i = 2; i <= temp; i++) {
			if (temp % i == 0) {
				divided_prime = i;
				temp = temp / divided_prime;
				break;
			}
		}
		cout << divided_prime << endl;
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
        long get_num = long.Parse(Console.ReadLine());
        while (get_num > 1)
        {
            long divided_prime = 0;
            for(long i = 2; i <= get_num; i++)
            {
                if(get_num % i == 0)
                {
                    divided_prime = i;
                    get_num = get_num / divided_prime;
                    break;
                }
            }
            Console.WriteLine(divided_prime);
        }
    }
}
```
