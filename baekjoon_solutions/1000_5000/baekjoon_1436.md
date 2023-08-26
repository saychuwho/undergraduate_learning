# baekjoon_1436

## C++ Solution

```c++
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	map<int, int> buffer;
	vector<int> doom_number;
	for (int i = 0; i < 10000; i++) {
		string using_case = "";
		for (int j = 0; j < 4-to_string(i).length(); j++) {
			using_case += "0";
		}
		using_case += to_string(i);
		int doom_locater = 0;
		while (doom_locater <= using_case.length()) {
			int w_indicator = 0, case_locater = 0;
			string temp_doom_number = "";
			while (w_indicator < using_case.length() + 3) {
				if (doom_locater == w_indicator) {
					temp_doom_number += "666";
					w_indicator += 3; doom_locater++;
				}
				else {
					temp_doom_number += using_case[case_locater];
					case_locater++; w_indicator++;
				}
			}
			if (buffer.find(stoi(temp_doom_number)) == buffer.end()) {
				buffer[stoi(temp_doom_number)] = 0;
				doom_number.push_back(stoi(temp_doom_number));
			}
		}
	}
	sort(doom_number.begin(), doom_number.end());
	int n = 0;
	cin >> n;
	cout << doom_number.at(n - 1);
}
```
