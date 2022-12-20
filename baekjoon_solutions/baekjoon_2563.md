# baekjoon_2563

## C++ Solution

In real, you need to deallocate dynamically allocated heap memory.

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int paper_num = 0, area = 0;
	cin >> paper_num;
	vector<pair<int, int>> coordinate;
	for (int i = 0; i < paper_num; i++) {
		int temp_1 = 0, temp_2 = 0;
		cin >> temp_1 >> temp_2;
		coordinate.push_back(pair<int, int>(temp_1, temp_2));
	}
	int max_x = coordinate[0].first, max_y = coordinate[0].second;
	for (int i = 1; i < paper_num; i++) {
		if (max_x < coordinate[i].first) {
			max_x = coordinate[i].first;
		}
		if (max_y < coordinate[i].second) {
			max_y = coordinate[i].second;
		}
	}
	max_x = max_x * 10, max_y = max_y * 10;
	int** plane = new int* [max_y];
	for (int i = 0; i < max_y; i++) {
		plane[i] = new int[max_x];
		for (int j = 0; j < max_x; j++) {
			plane[i][j] = 0;
		}
	}
	for (int i = 0; i < paper_num; i++) {
		for (int j = coordinate[i].second-1; j < coordinate[i].second + 9; j++) {
			for (int k = coordinate[i].first-1; k < coordinate[i].first + 9; k++) {
				plane[j][k] += 1;
			}
		}
	}
	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			if (plane[i][j] > 0) {
				area++;
			}
		}
	}
	cout << area;
} 
```
