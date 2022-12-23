# baekjoon_10814

## C++ Solution

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main() {
	int n = 0;
	cin >> n;
	map<int, vector<pair<int, string>>> get_data;
	for (int i = 0; i < n; i++) {
		int temp_age = 0; string temp_name = "";
		vector<pair<int, string>> temp_v;
		cin >> temp_age >> temp_name;
		if (get_data.find(temp_age) == get_data.end()) {
			temp_v.push_back(pair<int, string>(i, temp_name));
			get_data[temp_age] = temp_v;
		}
		else {
			get_data.find(temp_age)->second.push_back(pair<int, string>(i, temp_name));
		}
	}
	for (map<int, vector<pair<int, string>>>::iterator iter = get_data.begin(); iter != get_data.end(); iter++) {
		sort(iter->second.begin(), iter->second.end());
		for (vector<pair<int, string>>::iterator iter_v = iter->second.begin(); iter_v != iter->second.end(); iter_v++) {
			cout << iter->first << " " << iter_v->second << "\n";
		}
	}
}
```
