# baekjoon_10989

## C++ Solution

```c++
#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int counting_arr[10001];
	for (int i = 0; i < 10001; i++) {
		counting_arr[i] = 0;
	}
	int n = 0, max = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		cin >> temp;
		counting_arr[temp]++;
		if (i == 0) max = temp;
		if (i != 0 and max < temp) max = temp;
	}
	for (int i = 1; i <= max; i++) {
		if (counting_arr[i] == 0) 
			continue;
		else {
			for (int j = 0; j < counting_arr[i]; j++) {
				cout << i << "\n";
			}
		}
	}
} 
```
