# baekjoon_25501

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int recursion_num = 0;
int recursion(const char *s, int l, int r) {
	recursion_num++;
	if (l >= r) return 1;
	else if (s[l] != s[r]) return 0;
	else return recursion(s, l + 1, r - 1);
}
int isPalindrome(const char *s) {
	return recursion(s, 0, strlen(s) - 1);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 0;
	cin >> t;
	for (int i = 0; i < t; i++) {
		char s[1001];
		cin >> s;
		cout << isPalindrome(s) << " " << recursion_num << "\n";
		recursion_num = 0;
	}
} 
```
