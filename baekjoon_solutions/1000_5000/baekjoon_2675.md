# baekjoon_2675

## Ideas  

getline(cin, string) in C++ gets everyline untill press enter.

## C++ Solutions

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
	int t = 0;
	cin >> t;
	for (int k = 0; k < t; k++) {
		int n = 0;
		string getstr = "", result_str = "";
		cin >> n;
		getline(cin, getstr);
		if (getstr.empty()) {
			cout << result_str;
		}
		else {
			for (int i = 1; i < getstr.length(); i++) {
				for (int j = 0; j < n; j++) {
					result_str += getstr[i];
				}
			}
			cout << result_str << endl;
		}
	}
}
```

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        for(int i = 0; i < n; i++)
        {
            string[] get_info = Console.ReadLine().Split(' ');
            string result_str = "";
            for(int j=0; j < get_info[1].Length; j++)
            {
                for(int k=0; k < int.Parse(get_info[0]); k++)
                {
                    result_str += get_info[1][j];
                }
            }
            Console.WriteLine(result_str);
        }
    }
}
```
