# baekjoon_2935

## C# Solution

```c#
using System;

class HelloWorld
{
    static void Main(string[] args)
    {
        string a = Console.ReadLine();
        string operator_str = Console.ReadLine();
        string b = Console.ReadLine();
        if(a.Length < b.Length) { string temp = a; a = b; b = temp; }
        string result_str = a;
        if(operator_str == "*")
        {
            for(int i = 0; i < b.Length-1; i++)
            {
                result_str += "0";
            }
            if(b == "0") { result_str = "0"; }
        }
        else
        {
            if(a.Length == b.Length)
            {
                result_str = "2";
                for(int i = 0; i < a.Length-1; i++) { result_str += "0"; }
            }
            else {
                result_str = result_str.Remove(result_str.Length - b.Length);
                result_str += b;
            }
        }
        Console.WriteLine(result_str);
    }
}
```
