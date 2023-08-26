# baekjoon_2587

## C++ Solution

```c++
#include <iostream>
using namespace std;

void bubble_sort(int* A, int size) {
	for (int i = 0; i < size; i++) {
		int temp = size-1;
		for (int j = 0; j < temp; j++) {
			if (A[j] > A[j + 1]) {
				int temp_n = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp_n;
			}
		}
		temp--;
	}
}

int main() {
	int A[5];
	int exp = 0;
	for (int i = 0; i < 5; i++) {
		cin >> A[i];
		exp += A[i];
	}
	bubble_sort(A, 5);
	cout << exp / 5 << endl;
	cout << A[2];
}
```
