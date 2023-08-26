# baekjoon_2738

## C++ Solution

```c++
#include <iostream>
using namespace std;

int main() {
	int m = 0, n = 0;
	cin >> n >> m;
	int** A = new int* [n];
	int** B = new int* [n];
	int** C = new int* [n];
	for (int i = 0; i < n; i++) {
		A[i] = new int[m];
		B[i] = new int[m];
		C[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> B[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
} 
```
