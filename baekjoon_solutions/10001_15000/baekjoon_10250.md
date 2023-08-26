# baekjoon_10250

## C++ Solution

```c++
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	int t = 0;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int h = 0, w = 0, n = 0, x = 0, y = 0;
		cin >> h >> w >> n;
		string room_number = "";
		map<int, int> sequence;
		sequence.clear();
		sequence[y] = y * h; y++; sequence[y] = y * h;
		while (true) {
			if (sequence[y - 1] < n and sequence[y] >= n) {
				x = h - (sequence[y] - n);
				break;
			}
			else {
				y++;
				sequence[y] = y * h;
			}
		}
		if (y < 10) {
			room_number = to_string(x) + "0" + to_string(y);
		}
		else {
			room_number = to_string(x) + to_string(y);
		}
		cout << room_number << endl;
	}
}
```
