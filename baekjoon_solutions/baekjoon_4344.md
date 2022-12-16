# baekjoon_4344

## Idea

cout double precision

use cout << fixed;

```c++
cout << fixed;
cout.precision(3);
```

## C++ Solution

```c++
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    cout << fixed;
    cout.precision(3);
    int c = 0;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int n = 0;
        double exp = 0, over_avg = 0, percentage = 0;
        cin >> n;
        int* cases = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> cases[j];
        }
        for (int j = 0; j < n; j++) {
            exp += cases[j];
        }
        exp = exp / n;
        for (int j = 0; j < n; j++) {
            if (cases[j] > exp) {
                over_avg += 1;
            }
        }
        percentage = (over_avg / n)*100;
        percentage *= 1000;
        percentage = round(percentage);
        percentage = percentage/1000;
        cout << percentage << "%" << endl;
    }
}
```
