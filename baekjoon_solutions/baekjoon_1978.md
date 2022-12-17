# baekjoon_1978

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> getnum;
	int n = 0, counter = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		cin >> temp;
		getnum.push_back(temp);
	}
	for (int i = 0; i < getnum.size(); i++) {
		int temp = 0;
		if (getnum.at(i) == 1) {
			continue;
		}
		for (int j = 2; j < getnum.at(i); j++) {
			if (getnum.at(i) % j == 0) {
				temp++;
				break;
			}
		}
		if (temp == 0) {
			counter++;
		}
	}
	cout << counter;
} 
```
