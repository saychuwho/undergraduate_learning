# baekjoon_7568

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
	int n = 0;
	cin >> n;
	vector<vector<int>> cases(n);
	for (int i = 0; i < n; i++) {
		vector<int> temp(3);
		int x = 0, y = 0;
		cin >> x >> y;
		temp.at(0) = x;
		temp.at(1) = y;
		temp.at(2) = 1;
		cases.at(i) = temp;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (cases.at(i).at(0) < cases.at(j).at(0) and cases.at(i).at(1) < cases.at(j).at(1)) {
				cases.at(i).at(2)++;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << cases.at(i).at(2) << " ";
	}
}
```