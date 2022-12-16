# baekjoon_8958

## C++ Solution

```c++
#include <iostream>
#include <string>
using namespace std;
int main() {
    int n = 0;
    cin >> n;
    string* cases = new string[n];
    for (int i = 0; i < n; i++) {
        cin >> cases[i];
    }
    for (int i = 0; i < n; i++) {
        int score = 0;
        int temp_score = 0;
        for (int j = 0; j < cases[i].length(); j++) {
            if (cases[i][j] == 'X') {
                temp_score = 0;
            }
            else {
                temp_score += 1;
                score += temp_score;
            }
        }
        cout << score << endl;
    }
    delete[] cases;
}
```
