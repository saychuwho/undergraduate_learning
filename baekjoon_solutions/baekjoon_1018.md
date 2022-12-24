# baekjoon_1018

## C++ Solution

```c++
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
int main() {
	int n = 0, m = 0; int min = 64;
	int counter[4];
	for (int i = 0; i < 4; i++) counter[i] = 0;
	string start_B = "BWBWBWBW", start_W = "WBWBWBWB";
	cin >> n >> m;
	string* get_chess = new string[n];
	for (int i = 0; i < n; i++)
		cin >> get_chess[i];
	int max_n_index = n - 8;
	int max_m_index = m - 8;
	map<pair<int, int>, int> cases;
	for (int i = 0; i <= max_n_index; i++) {
		for (int j = 0; j <= max_m_index; j++)
			cases[pair<int, int>(i, j)] = 0;
	}
	for (map<pair<int, int>, int>::iterator iter = cases.begin(); iter != cases.end(); iter++) {
		int line = 0;
		for (int i = iter->first.first; i < iter->first.first+8; i++) {
			// not reverse
			if (get_chess[iter->first.first][iter->first.second] == 'B') {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][j] != start_B[j- iter->first.second]) 
							counter[0]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][j] != start_W[j - iter->first.second])
							counter[0]++;
					}
				}
			}
			else {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][j] != start_W[j - iter->first.second])
							counter[0]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][j] != start_B[j - iter->first.second])
							counter[0]++;
					}
				}
			}
			// n m all reverse
			if (get_chess[n - 1 - iter->first.first][m - 1 - iter->first.second] == 'B') {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][m - 1 - j] != start_B[j - iter->first.second])
							counter[1]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][m - 1 - j] != start_W[j - iter->first.second])
							counter[1]++;
					}
				}
			}
			else {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][m - 1 - j] != start_W[j - iter->first.second])
							counter[1]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][m - 1 - j] != start_B[j - iter->first.second])
							counter[1]++;
					}
				}
			}
			// only n reverse
			if (get_chess[n - 1 - iter->first.first][iter->first.second] == 'B') {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][j] != start_B[j - iter->first.second])
							counter[2]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][j] != start_W[j - iter->first.second])
							counter[2]++;
					}
				}
			}
			else {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][j] != start_W[j - iter->first.second])
							counter[2]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[n - 1 - i][j] != start_B[j - iter->first.second])
							counter[2]++;
					}
				}
			}
			// only m reverse
			if (get_chess[iter->first.first][m-1-iter->first.second] == 'B') {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][m-1-j] != start_B[j - iter->first.second])
							counter[3]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][m-1-j] != start_W[j - iter->first.second])
							counter[3]++;
					}
				}
			}
			else {
				if (line % 2 == 0) {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][m - 1 - j] != start_W[j - iter->first.second])
							counter[3]++;
					}
				}
				else {
					for (int j = iter->first.second; j < iter->first.second + 8; j++) {
						if (get_chess[i][m - 1 - j] != start_B[j - iter->first.second])
							counter[3]++;
					}
				}
			}
			line++;
		}
		sort(counter, counter + 4);
		if (counter[0] < min) min = counter[0];
		for (int k = 0; k < 4; k++) counter[k] = 0;
	}
	cout << min;
}
```
