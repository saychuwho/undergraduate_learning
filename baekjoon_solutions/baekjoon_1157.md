# baekjoon_1157

## Idea  

Use the map appropriatly

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	map<char, int> alpha_num;
	for (int i = 0; i < 26; i++) {
		alpha_num.insert(pair<char, int>(char(i + 65), 0));
	}
	string getstr;
	cin >> getstr;
	for (map<char, int>::iterator i = alpha_num.begin(); i != alpha_num.end(); i++) {
		for (int j = 0; j < getstr.length(); j++) {
			if (int(getstr[j]) == int(i->first) or (int(getstr[j]) - 32) == int(i->first)) {
				i->second += 1;
			}
		}
	}
	map<char, int>::iterator max_iter = alpha_num.begin();
	int temp_counter = 0;
	for (map<char, int>::iterator i = ++alpha_num.begin(); i != alpha_num.end(); i++) {
		if (max_iter->second < i->second) {
			max_iter = i;
			temp_counter = 0;
		}
		else if (max_iter->second == i->second) {
			temp_counter += 1;
		}
	}
	if (temp_counter > 0) {
		cout << "?";
	}
	else {
		cout << max_iter->first;
	}
}
```
