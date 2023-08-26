# baekjoon_11720

## Ideas  

In C++, when turn char type number charactor to int type number, consider the ascii code and make like this.

```c++
char a = '1';
int b = 0;
// ascii code 48 is '0'
b = int(a) - 48;
```

## C++ Solution

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
	int n = 0, sum = 0;
	string number = "";
	cin >> n;
	cin >> number;
	int* cal_num_arr = new int[n];
	for (int i = 0; i < n; i++) {
		cal_num_arr[i] = int(number[i]) - 48;
		sum += cal_num_arr[i];
	}
	cout << sum;
	delete[] cal_num_arr;
}
```
