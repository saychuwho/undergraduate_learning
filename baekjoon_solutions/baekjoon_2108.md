# baekjoon_2108

## C++ Solution

```c++
#include <iostream>
using namespace std;

int round(int total, int n) {
	int judge = 0;
	if (n % 2 == 0)
		judge = n / 2;
	else
		judge = n / 2 + 1;
	if (total > 0) {
		if (total % n >= judge)
			return total / n + 1;
		else
			return total / n;
	}
	if (total < 0) {
		if (total % n <= judge*-1)
			return total / n - 1;
		else
			return total / n;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n = 0, min = 0, max = 0, total = 0, mid = 0, accumulation = 0, mode_index = 0, mid_index = 0, range = 0, mode_counter = 0;
	int data[8002];
	for (int i = 0; i < 8002; i++) {
		data[i] = 0;
	}
	cin >> n;
	if (n % 2 == 0)
		mid = n / 2;
	else
		mid = (n / 2) + 1;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		cin >> temp;
		total += temp; //
		data[temp + 4000]++;
		if (i == 0) {
			min = temp + 4000;
			max = temp + 4000;
		}
		else if (min > temp + 4000)
			min = temp + 4000;
		else if (max < temp + 4000)
			max = temp + 4000;
	}
	range = max - min; // 
	accumulation = 0;
	mode_index = min;
	for (int i = min; i <= max; i++) {
		if (data[mode_index] < data[i]) {
			mode_index = i;
			mode_counter = 0;
		}
		else if (data[mode_index] == data[i] and mode_counter < 1 and i!=min) {
			mode_index = i;
			mode_counter++;
		}
		if (accumulation < mid and accumulation + data[i] >= mid) {
			mid_index = i; // 
		}
		accumulation += data[i];
	}
	cout << round(total, n) << "\n";
	cout << mid_index-4000 << "\n";
	cout << mode_index - 4000 << "\n";
	cout << range;
} 
```
