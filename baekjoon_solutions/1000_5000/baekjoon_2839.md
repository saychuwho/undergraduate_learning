# baekjoon_2839

## C++ Solution

```c++
#include <iostream>
#include <map>
using namespace std;

int main() {
	int n = 0;
	cin >> n;
	map<int, int> ordered_pair; 
	int a = 0, b = 0, b_r = 0;
	while (true) {
		b = ((-3 * a) + n) / 5;
		b_r = ((-3 * a) + n) % 5;
		if (b < 0) {
			break;
		}
		if (b_r > 0 or b_r<0) {
			a++;
			continue;
		}
		ordered_pair[a] = b;
		a++;
	}
	if (ordered_pair.size() == 0) {
		cout << -1;
	}
	else {
		int bag_num = ordered_pair.begin()->first + ordered_pair.begin()->second;
		for (map<int, int>::iterator i = ordered_pair.begin(); i != ordered_pair.end(); i++) {
			if (bag_num > i->first + i->second) {
				bag_num = i->first + i->second;
			}
		}
		cout << bag_num;
	}
}
```
