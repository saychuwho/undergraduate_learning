# baekjoon_1181

## C++ Solution

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
bool compare(string a, string b) {
	if (a.length() < b.length())
		return true;
	else if (a.length() > b.length())
		return false;
	else
		return a < b;
}
int main() {
	int n = 0;
	cin >> n;
	vector<string> get_word(n);
	for (int i = 0; i < n; i++) {
		cin >> get_word.at(i);
	}
	sort(get_word.begin(), get_word.end(), compare);
	for (int i = 0; i < n; i++) {
		if (i<n-1 and get_word.at(i) == get_word.at(i + 1))
			continue;
		cout << get_word.at(i) << "\n";
	}
}
```
