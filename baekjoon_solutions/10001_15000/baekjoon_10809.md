# baekjoon_10809

## C++ Solution

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
	string getstr = "";
	cin >> getstr;
	for (int i = 0; i < 26; i++) {
		char temp_ch = char(i + 97);
		int temp_counter = -1;
		for (int j = 0; j < getstr.length(); j++) {
			if (temp_ch == getstr[j]) {
				temp_counter += j+1;
				break;
			}
		}
		cout << temp_counter << " ";
	}
}
```
