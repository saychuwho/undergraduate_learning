# baekjoon_2292

## C++ Solution

```c++
#include <iostream>
#include <map>
using namespace std;

int main() {
	map<int, long long> layer;
	layer.insert(pair<int, long long>(1, 1));
	layer.insert(pair<int, long long>(2, 7));
	long long n = 0;
	cin >> n;
	int i = 2, room_num = 1;
	while (true) {
		if (n == 1) {
			break;
		}
		else if (layer[i-1] < n and n <= layer[i]) {
			room_num = layer.find(i)->first;
			break;
		}
		else {
			layer.insert(pair<int, long long>(i + 1, layer[i] + (6 * i)));
			i++;
		}
	}
	cout << room_num;
}
```
