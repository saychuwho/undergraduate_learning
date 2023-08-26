# baekjoon_1065

## C++ Solution

```c++
#include <iostream>

using namespace std;

bool hansu(int n) {
	int n_100 = n/100, n_10 = (n%100)/10, n_1 = (n%10);
	if (n_100 == 0) {
		return true;
	}
	else if (n_100 == 0 and n_10 == 0) {
		return true;
	}
	else {
		if (n_100 - n_10 == n_10 - n_1) {
			return true;
		}
		else {
			return false;
		}
	}
}

int main() {
	int N = 0, counter = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		if (hansu(i)) {
			counter += 1;
		}
	}
	cout << counter;
}
```
