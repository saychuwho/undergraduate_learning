# backjoon_1929

## IDEAS

Use sieve of Eratosthenes to avoid time over.

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	vector<int> prime;
	vector<int> getnum;
	int m = 0, n = 0;
	cin >> m >> n;
	for (int i = 2; i <= n; i++) {
		getnum.push_back(i);
	}
	prime.push_back(2);
	int w_condition = prime.at(prime.size() - 1) * prime.at(prime.size() - 1);
	while (w_condition <= n) {
		int last_prime = prime.size() - 1;
		int next_prime = 1, previous_prime = 1;
		for (int i = 0; i < getnum.size(); i++) {
			if (getnum.at(i) == 0) {
				continue;
			}
			if (next_prime == previous_prime and getnum.at(i) % prime.at(last_prime) != 0 and getnum.at(i)>prime.at(last_prime)) {
				prime.push_back(getnum.at(i));
				next_prime = 0;
			}
			if (getnum.at(i) % prime.at(last_prime) == 0 and getnum.at(i) != prime.at(last_prime)) {
				getnum.at(i) = 0;
			}
		}
		w_condition = prime.at(prime.size() - 1) * prime.at(prime.size() - 1);
	}
	for (int i = 0; i < getnum.size(); i++) {
		if (getnum.at(i) >= m) {
			cout << getnum.at(i) << "\n";
		}
	}
} 
```
