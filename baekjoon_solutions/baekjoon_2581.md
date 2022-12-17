# baekjoon_2581

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int m = 0, n = 0, sum = 0;
	cin >> m >> n;
	vector<int> prime;
	for (int i = m; i <= n; i++) {
		int temp = 0;
		if (i == 1) {
			continue;
		}
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				temp++;
				break;
			}
		}
		if (temp == 0) {
			prime.push_back(i);
		}
	}
	if (prime.size() != 0) {
		for (vector<int>::iterator i = prime.begin(); i != prime.end(); i++) {
			sum += *i;
		}
		cout << sum << endl;
		cout << prime.at(0);
	}
	else {
		cout << -1;
	}
}
```
