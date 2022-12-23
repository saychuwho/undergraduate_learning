# baekjoon_2231

## C++ Solution

```c++
#include <iostream>
#include <string>
using namespace std;
int main() {
	int n = 0, m = 0;
	cin >> n;
	for (int i = n - 9 * to_string(n).length(); i < n; i++) {
		int temp = i;
		for (int j = 0; j < to_string(i).length(); j++) {
			temp += int(to_string(i)[j])-48;
		}
		if (temp == n) {
			m = i;
			break;
		}
	}
	cout << m;
}
```
