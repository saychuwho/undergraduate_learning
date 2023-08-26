# baekjoon_11651

## C++ Solution

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main() {
	map<int, vector<int>> getnum;
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp_x = 0, temp_y = 0;
		cin >> temp_x >> temp_y;
		vector<int> temp_v;
		if (getnum.find(temp_y) == getnum.end()) {
			temp_v.push_back(temp_x);
			getnum[temp_y] = temp_v;
		}
		else {
			getnum.find(temp_y)->second.push_back(temp_x);
		}
	}
	for (map<int, vector<int>>::iterator iter = getnum.begin(); iter != getnum.end(); iter++) {
		sort(iter->second.begin(), iter->second.end());
		for (vector<int>::iterator iter_v = iter->second.begin(); iter_v != iter->second.end(); iter_v++) {
			cout << *iter_v << " " << iter->first << "\n";
		}
	}
}
```
