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
