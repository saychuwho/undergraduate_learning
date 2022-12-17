# baekjoon_1316

## Ideas  

In C++, when you add elements into vector with push_back(), previous iterator of vector is disabled. so you need to use different method.

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int n = 0, counter = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string word = "";
		cin >> word;
		vector<char> temp_v;
		temp_v.push_back(word[0]);
		int temp_v_end = 0, temp_counter = 0;
		for (int j = 1; j < word.length(); j++) {
			if (word[j - 1] != word[j]) {
				for(int k=0;k<=temp_v_end;k++){
					if (temp_v.at(k) == word[j]) {
						temp_counter += 1;
						break;
					}
				}
				if (temp_counter == 0) {
					temp_v.push_back(word[j]);
					temp_v_end++;
				}
			}
			if (temp_counter > 0) {
				counter += -1;
				break;
			}
		}
	}
	cout << n + counter;
}
```
