# baekjoon_2447

## C++ Solution

```c++
#include <iostream>
using namespace std;
void stardrawing(int** plane, int start_i, int start_j, int n, bool indicator) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (n == 3 and indicator == false) {
				if (i != 1 or j != 1) {
					plane[start_i + i][start_j + j] = 42;
				}
				else if (i == 1 and j == 1) {
					plane[start_i + i][start_j + j] = 32;
				}
			}
			else if (n == 3 and indicator == true) {
				plane[start_i + i][start_j + j] = 32;
			}
			else if(n>3 and indicator == false) {
				if (i != 1 or j != 1) {
					stardrawing(plane, start_i + i * (n / 3), start_j + j * (n / 3), n / 3, false);
				}
				else if(i==1 and j==1) {
					stardrawing(plane, start_i + i * (n / 3), start_j + j * (n / 3), n / 3, true);
				}
			}
			else {
				stardrawing(plane, start_i + i * (n / 3), start_j + j * (n / 3), n / 3, true);
			}
		}
	}
}

int main() {
	int n = 0;
	cin >> n;
	int** stars = new int* [n];
	for (int i = 0; i < n; i++) {
		stars[i] = new int[n];
		for (int j = 0; j < n; j++) {
			stars[i][j] = 0;
		}
	}

	stardrawing(stars, 0, 0, n, false);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << char(stars[i][j]);
		}
		cout << "\n";
	}
	for (int i = 0; i < n; i++) {
		delete[] stars[i];
	}
	delete[] stars;
} 
```
