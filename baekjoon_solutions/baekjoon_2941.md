# baekjoon_2941

## C++ Solution

```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
	string getstr = "";
	cin >> getstr;
	int i = 0, counter = 0;
	while (i < getstr.length()) {
		if (getstr[i] == 'l' and getstr[i + 1] == 'j' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else if (getstr[i] == 'c' and getstr[i + 1] == '=' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else if (getstr[i] == 'c' and getstr[i + 1] == '-' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else if (getstr[i] == 'd' and getstr[i + 1] == 'z' and getstr[i+2] == '=' and i < getstr.length() - 1) {
			counter += 1;
			i += 3;
		}
		else if (getstr[i] == 'd' and getstr[i + 1] == '-' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else if (getstr[i] == 'n' and getstr[i + 1] == 'j' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else if (getstr[i] == 's' and getstr[i + 1] == '=' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else if (getstr[i] == 'z' and getstr[i + 1] == '=' and i < getstr.length() - 1) {
			counter += 1;
			i += 2;
		}
		else {
			counter += 1;
			i += 1;
		}
	}
	cout << counter;
}
```