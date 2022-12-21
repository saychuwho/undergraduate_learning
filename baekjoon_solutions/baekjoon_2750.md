# baekjoon_2750

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
	int n = 0;
	cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	bubble_sort(A, n);
	for (int i = 0; i < n; i++) {
		cout << A[i] << "\n";
	}
	delete[] A;
} 
```
