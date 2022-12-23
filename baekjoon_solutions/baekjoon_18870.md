# baekjoon_18870

## C++ Solution

```c++
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
int main() {
	int n = 0;
	cin >> n;
	int* get_arr = new int[n];
	map<int, int> real_x;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		cin >> temp;
		get_arr[i] = temp;
		if (real_x.find(temp) == real_x.end()) {
			real_x[temp] = 0;
		}
	}
	int temp = 0;
	for (map<int, int>::iterator iter = real_x.begin(); iter != real_x.end(); iter++) {
		iter->second += temp;
		temp++;
	}	
	for (int i = 0; i < n; i++) {
		cout << real_x.find(get_arr[i])->second << " ";
	}
}
```
