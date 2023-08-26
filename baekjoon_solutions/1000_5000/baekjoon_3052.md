# baekjoon_3052

## C++ Solution

```c++
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> numbers;
    vector<int> remainders;
    for (int i = 0; i < 10; i++) {
        int temp = 0;
        cin >> temp;
        numbers.push_back(temp);
    }
    remainders.push_back(numbers.at(0) % 42);
    for (int i = 1; i < numbers.size(); i++) {
        int indicator = 0;
        for (int j = 0; j < remainders.size(); j++) {
            if (numbers.at(i) % 42 == remainders.at(j)) {
                indicator++;
            }
        }
        if (indicator == 0) {
            remainders.push_back(numbers.at(i) % 42);
        }
    }
    cout << remainders.size();
}
```
