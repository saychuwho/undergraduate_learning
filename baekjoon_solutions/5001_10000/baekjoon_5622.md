# baekjoon_5622

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	map<char, int> tele_alpha_second;
	int i = 65;
	int second = 3;
	while(i<91) {
		if((i>=80 and i < 84)or(i>=87 and i<91)){
			tele_alpha_second.insert(pair<char, int>(char(i), second));
			tele_alpha_second.insert(pair<char, int>(char(i + 1), second));
			tele_alpha_second.insert(pair<char, int>(char(i + 2), second));
			tele_alpha_second.insert(pair<char, int>(char(i + 3), second));
			i += 4;
			second += 1;
		}
		else {
			tele_alpha_second.insert(pair<char, int>(char(i), second));
			tele_alpha_second.insert(pair<char, int>(char(i + 1), second));
			tele_alpha_second.insert(pair<char, int>(char(i + 2), second));
			i += 3;
			second += 1;
		}
	}
	string grandma_telenum = "";
	int total_time = 0;
	std::cin >> grandma_telenum;
	for (int i = 0; i < grandma_telenum.length(); i++) {
		total_time += tele_alpha_second.find(grandma_telenum[i])->second;
	}
	cout << total_time;
}
```
