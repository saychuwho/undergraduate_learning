# baekjoon_3003

## problem

Chess has total 16 pieces. (1 King, 1 Queen, 2 Rook, 2 Bishop, 2 Knight, 8 pawn)

Calculate how many pieces needed to add or take away. order of input is king, queen, rook, bishop, knight, pawn.

If number is positive, pieces should be added like that number. If number is negative, pieces should be taken away like that number.

### input 1

```c++
0 1 2 2 2 7
```

### output 1

```c++
1 0 0 0 0 1
```

### input 2

```c++
2 1 2 1 2 1
```

### output 2

```c++
-1 0 0 1 0 7
```

## Ideas  

Calculate each pieces needed.

## C++ Solution

```c++
#include <iostream>

int main() {
    int k{ 0 }, q{ 0 }, r{ 0 }, b{ 0 }, kn{ 0 }, p{ 0 };
    std::cin >> k >> q >> r >> b >> kn >> p;
    std::cout << -1*(k - 1) << " " << -1*(q - 1) << " " << -1*(r - 2) << " " << -1*(b - 2) << " " << -1*(kn - 2) << " " << -1*(p - 8);
}
```
