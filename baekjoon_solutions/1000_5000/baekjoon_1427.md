# baekjoon_1427

## C++ Solution

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
	int counted_num[10];
	for (int i = 0; i < 10; i++) {
		counted_num[i] = 0;
	}
	string number = "";
	cin >> number;
	for (int i = 0; i < number.length(); i++) {
		counted_num[int(number[i]) - 48]++;
	}
	for (int i = 1; i <= 10; i++) {
		if (counted_num[10 - i] == 0)
			continue;
		for (int j = 0; j < counted_num[10 - i]; j++) {
			cout << 10 - i;
		}
	}
}
```
