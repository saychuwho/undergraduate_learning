# baekjoon_2798

## C++ Solution

```c++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
	int n = 0, m = 0, max = 0;
	cin >> n >> m;
	int* card_num = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> card_num[i];
	}
	vector<int> cases;
	for (int i = 0; i < n-2; i++) {
		for (int j = i + 1; j < n - 1; j++) {
			for (int k = j + 1; k < n; k++) {
				cases.push_back(card_num[i] + card_num[j] + card_num[k]);
			}
		}
	}
	for (vector<int>::iterator iter = cases.begin(); iter != cases.end(); iter++) {
		if (max < *iter and *iter <= m) {
			max = *iter;
		}
	}
	cout << max;
	delete[] card_num;
}
```
