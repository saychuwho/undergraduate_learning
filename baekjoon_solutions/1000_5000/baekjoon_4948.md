# baekjoon_4948

## IDEA

Calculate all possible prime numbers first. And then count the prime number fits with initial condition.

## C++ Solution

### Passed solution

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	bool is_prime[2*123456];
	for (int i = 0; i < 2*123456; i++) {
		if (i == 0)
			is_prime[i] = false;
		else
			is_prime[i] = true;
	}

	int prime_use = 2;
	int w_con = 0;
	while (w_con < 2*123456) {
		bool indicator = true;
		int temp_prime = 0;
		w_con = prime_use * prime_use;
		for (int i = 0; i < 2*123456; i++) {
			if (is_prime[i] == false) {
				continue;
			}
			if ((i + 1) % prime_use == 0 and (i + 1) != prime_use) {
				is_prime[i] = false;
			}
			if (indicator == true and (i + 1) % prime_use != 0 and (i + 1) > prime_use) {
				temp_prime = i + 1;
				indicator = false;
			}
		}
		prime_use = temp_prime;
	}

	while (true) {
		int n = 0, counter = 0;
		cin >> n;
		if (n == 0)
			break;
		for (int i = n; i <= 2*n-1; i++) {
			if (is_prime[i] == true)
				counter++;
		}
		cout << counter << "\n";
	}
} 
```

### worked, but has time out problem

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	vector<int> prime;
	while (true) {
		prime.clear();
		vector<int>().swap(prime);
		int n = 0, min_n = 0, max_n = 0, counter = 0;
		cin >> n;
		if (n == 0) {
			break;
		}
		min_n = n; max_n = 2 * n;
		int getnum_size = max_n - 1;
		int* getnum = new int[getnum_size];
		for (int i = 2; i <= max_n; i++) {
			getnum[i-2] = i;
		}
		prime.push_back(2);
		int w_condition = 0;
		while (w_condition < max_n) {
			int last_prime = prime.size() - 1;
			int next_prime = 1, previous_prime = 1;
			w_condition = prime.at(prime.size() - 1) * prime.at(prime.size() - 1);
			for (int i = 0; i < getnum_size; i++) {
				if (getnum[i] == 0) {
					continue;
				}
				if (next_prime == previous_prime and getnum[i] % prime.at(last_prime) != 0 and getnum[i] > prime.at(last_prime)) {
					prime.push_back(getnum[i]);
					next_prime = 0;
				}
				if (getnum[i] % prime.at(last_prime) == 0 and getnum[i] != prime.at(last_prime)) {
					getnum[i] = 0;
				}
				if (w_condition >= max_n and getnum[i] != 0 and getnum[i]>min_n) {
					counter++;
				}
			}
		}
		cout << counter << "\n";
		delete[] getnum;
	}
} 
```

### Changed code not using vector, but it still have time out problem

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	while (true) {
		int n = 0, min_n=0, max_n=0, counter = 0;
		cin >> n;
		if (n == 0) {
			break;
		}
		min_n = n; max_n = 2 * n;
		bool* getnum = new bool[max_n];
		for (int i = 0; i < max_n; i++) {
			if (i == 0) {
				getnum[i] = false;
			}
			else {
				getnum[i] = true;
			}
		}
		int prime_use = 2;
		int w_con = 0;
		while (w_con < max_n) {
			bool indicator = true;
			int temp_prime = 0;
			w_con = prime_use * prime_use;
			for (int i = 0; i < max_n; i++) {
				if (getnum[i] == false) {
					continue;
				}
				if ((i + 1) % prime_use == 0 and (i + 1) != prime_use) {
					getnum[i] = false;
				}
				if (w_con >= max_n and getnum[i] == true and (i + 1) > min_n) {
					counter++;
				}
				if (indicator == true and (i + 1) % prime_use != 0 and (i + 1) > prime_use) {
					temp_prime = i + 1;
					indicator = false;
				}
			}
			prime_use = temp_prime;
		}
		cout << counter << "\n";
		delete[] getnum;
	}
} 
```
