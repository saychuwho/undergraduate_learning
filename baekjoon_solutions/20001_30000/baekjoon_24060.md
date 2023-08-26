# baekjoon_24060

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;

vector<int> counter;

int* merge(int* left, int* right, int left_size, int right_size) {
	int* result = new int[left_size + right_size];
	int i = 0, j = 0, t=0;
	while (i < left_size and j < right_size) {
		if (left[i] <= right[j]) {
			result[t] = left[i];
			counter.push_back(left[i]);
			t++;
			i++;
		}
		else {
			result[t] = right[j];
			counter.push_back(right[j]);
			t++;
			j++;
		}
	}
	while (i < left_size) {
		result[t] = left[i];
		counter.push_back(left[i]);
		t++;
		i++;
	}
	while (j < right_size) {
		result[t] = right[j];
		counter.push_back(right[j]);
		t++;
		j++;
	}
	return result;
}

int* merge_sort(int* A, int n) {
	int A_size = n;
	if (A_size < 2) {
		return A;
	}
	int mid = A_size / 2;
	int left_size = 0, right_size = 0;
	if (A_size % 2 != 0) {
		left_size = mid + 1;
		right_size = A_size - left_size;
	}
	else {
		left_size = mid;
		right_size = A_size - left_size;
	}
	int* left = new int[left_size];
	int* right = new int[right_size];
	for (int i = 0; i < left_size; i++) {
		left[i] = A[i];
	}
	for (int i = 0; i < right_size; i++) {
		right[i] = A[i+left_size];
	}
	int* result_left = merge_sort(left, left_size);
	int* result_right = merge_sort(right, right_size);
	return merge(result_left, result_right, left_size, right_size);
}

int main() {
	int n = 0, k = 0;
	cin >> n >> k;
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	int* sorted_A = merge_sort(A, n);
	if (k > counter.size()) {
		cout << -1;
	}
	else {
		cout << counter.at(k - 1);
	}
} 
```
