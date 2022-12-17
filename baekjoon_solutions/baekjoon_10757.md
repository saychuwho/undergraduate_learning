# baekjoon_10757

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	string a, b, large, small, result = "";
	cin >> a >> b;
	if (a > b and a.length() == b.length()) {
		large = a; small = b;
	}
	else if (a.length() > b.length()) {
		large = a; small = b;
	}
	else {
		large = b; small = a;
	}
	reverse(large.begin(), large.end());
	reverse(small.begin(), small.end());
	int go_up = 0, remain = 0;
	for (int i = 0; i < small.length(); i++) {
		int sum = (int(large[i]) - 48) + (int(small[i]) - 48) + go_up;
		remain = sum % 10;
		go_up = sum / 10;
		result += char(remain + 48);
	}
	 
	for (int i = small.length(); i < large.length(); i++) {
		if (go_up > 0) {
			int sum = (int(large[i]) - 48) + go_up;
			remain = sum % 10;
			go_up = sum / 10;
			result += char(remain + 48);
		}
		else {
			result += large[i];
		}
	}
	if (go_up > 0) {
		result += char(go_up + 48);
	}
	
	reverse(result.begin(), result.end());
	cout << result;
} 
```
