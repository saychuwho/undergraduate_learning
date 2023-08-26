# baekjoon_1712

## Ideas 

Always aware of divisionByZero when making algorithm with division.

## C++ Solution

```c++
#include <iostream>
using namespace std;

int main() {
	long long a = 0, b = 0, c = 0, n=0;
	cin >> a >> b >> c;
	if (c - b != 0) {
		n = (a / (c - b)) + 1;
		if (n < 0) {
			n = -1;
		}
	}
	else {
		n = -1;
	}
	cout << n;
}
```
