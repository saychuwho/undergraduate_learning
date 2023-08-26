# baekjoon_9020

## C++ Solution

```c++
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	bool is_prime[10000];
	vector<int> prime;
	for (int i = 0; i < 10000; i++) {
		if (i == 0)
			is_prime[i] = false;
		else
			is_prime[i] = true;
	}
	int prime_use = 2;
	int w_con = 0;
	while (w_con < 10000) {
		bool indicator = true;
		int temp_prime = 0;
		w_con = prime_use * prime_use;
		for (int i = 0; i < 10000; i++) {
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
			if (w_con >= 10000 and is_prime[i] == true) {
				prime.push_back(i + 1);
			}
		}
		prime_use = temp_prime;
	}
	int t = 0;
	cin >> t;
	map<int, int> partition;
	for (int i = 0; i < t; i++) {	
		partition.clear();
		int n = 0;
		cin >> n;
		int j = 0, k = 0;
		while (prime.at(j) < n and j<prime.size()-1) {
			k = j;
			while (prime.at(k) < n and k<prime.size()-1) {
				if (prime.at(j) + prime.at(k) == n) {
					partition[prime.at(j)] = prime.at(k);
				}
				k++;
			}
			j++;
		}
		map<int, int>::iterator partition_last = partition.end();
		partition_last--;
		cout << partition_last->first << " " << partition_last->second << "\n";
	}
} 
```
