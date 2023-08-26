# baekjoon_2775

## C++ Solution

```c++
#include <iostream>
using namespace std;
int living_people(int a, int b) {
	int result_num = 0;
	if (a == 0) {
		return b;
	}
	else {
		for (int i = 1; i <= b; i++) {
			result_num += living_people(a - 1, i);
		}
		return result_num;
	}
}
int main() {
	int t = 0;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int k = 0, n = 0;
		cin >> k >> n;
		cout << living_people(k, n) << endl;
	}
}
```
