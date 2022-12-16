# baekjoon_1546

## Ideas  

you need to use double type when you need accurate division.

## C++ Solution

```c++
#include <iostream>
using namespace std;
int main() {
    cout.precision(10);
    int n = 0;
    double highest_score = 0;
    double exp = 0;
    cin >> n;
    int* score = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> score[i];
    }
    highest_score = score[0];
    for (int i = 1; i < n; i++) {
        if (highest_score < score[i]) {
            highest_score = score[i];
        }
    }
    for (int i = 0; i < n; i++) {
        exp = exp + score[i];
    }
    double new_exp = (exp / n)*(100/highest_score);
    cout << new_exp;
}
```
