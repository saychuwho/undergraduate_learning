# baekjoon_11729

## IDEA

When solving recursion problem, you first define problems with functions, and get Ideas from small cases, and make that small cases with recursion form. 

In this case, tower of hanoi problem can be changed like this

> hanoi(N, 'A', 'C', 'B') : get disk number n and print all cases to move all disk from 'A' to 'C' via 'B'

And inside hanoi(3), we can find pattern like this

> hanoi(3, 'A', 'C', 'B') = hanoi(2, 'A', 'B', 'C') + move(3, 'A', 'C') + hanoi(2, 'B', 'C', 'A')

So, we can make hanoi function like this

> move(N, 'A', 'B') : move N th disk from 'A' to 'B'
> 
> hanoi(N, 'A', 'C', 'B'){
>   
>   (if n == 1) move(1, 'A', 'C')
>   
>   (else) hanoi(N-1, 'A', 'B', 'C') + move(N, 'A', 'C') + hanoi(N-1, 'B', 'C', 'A')
>   
> }

## C++ Solution

```c++
#include <iostream>
#include <string>
using namespace std;

int hanoi_called = 0;
string progress = "";

void move(int start, int to) {
	progress += to_string(start) + " " + to_string(to) + "\n";
}

void hanoi(int n, int start, int to, int via) {
	hanoi_called++;
	if (n == 1) {
		move(start, to);
	}
	else {
		hanoi(n - 1, start, via, to);
		move(start, to);
		hanoi(n - 1, via, to, start);
	}
}


int main() {
	int n = 0;
	cin >> n;
	hanoi(n, 1, 3, 2);
	cout << hanoi_called << "\n";
	cout << progress;
} 
```