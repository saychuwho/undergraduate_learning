# baekjoon_1193

## C++ Solution

```c++
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	map<long long, long long> sequence;
	sequence[1] = 1;
	sequence[2] = 3;
	long long i = 2; long long x = 0; string result_fraction = "1/1";
	cin >> x;
	while (true) {
		if (x == 1) {
			break;
		}
		else if (sequence[i - 1] < x and sequence[i] >= x) {
			long long denominator = sequence[i] - x+1;
			long long numerator = i+1 -denominator;
			if (i % 2 == 0) {
				result_fraction = to_string(numerator) + "/" + to_string(denominator);
			}
			else {
				result_fraction = to_string(denominator) + "/" + to_string(numerator);
			}
			break;
		}
		else {
			sequence[i + 1] = sequence[i] + i + 1;
			i++;
		}
	}
	cout << result_fraction;
}
```
