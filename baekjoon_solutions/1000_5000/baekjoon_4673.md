# baekjoon_4673

## C++ Solution

```c++
#include <iostream>

using namespace std;

int d(int n) {
	return n + (n / 1000) + ((n % 1000) / 100) + ((n % 100) / 10) + (n % 10);
}

int main() {
	for (int i = 1; i <= 10000; i++) {
		int indicator = 0;
		for (int j = 1; j <= i; j++) {
			if (d(j) == i) {
				indicator += 1;
				break;
			}
		}
		if (indicator == 0) {
			cout << i << endl;
		}
	}
}
```
