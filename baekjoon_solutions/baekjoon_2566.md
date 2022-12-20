# baekjoon_2566

## C++ Solution

```c++
#include <iostream>
using namespace std;

int main() {
	int A[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> A[i][j];
		}
	}
	int max = 0, max_i = 0, max_j = 0;
	max = A[max_i][max_j];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (max < A[i][j]) {
				max = A[i][j];
				max_i = i, max_j = j;
			}
		}
	}
	cout << max << endl;
	cout << max_i + 1 << " " << max_j+1;
} 
```
