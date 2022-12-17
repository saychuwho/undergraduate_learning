# baekjoon_2869

## C++ Solution

```c++
#include <iostream>
using namespace std;

int main() {
	long long day = 0, night = 0, top_d= 0, day_passes = 0, climed_d = 0;
	cin >> day >> night >> top_d;
	long long temp = (top_d - day) % (day - night);
	day_passes = (top_d - day) / (day - night) + 1;
	if (temp > 0) {
		day_passes++;
	}
	cout << day_passes;
}
```
