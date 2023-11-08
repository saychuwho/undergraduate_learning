N = int(input())
A_input = input().split()
A = dict()
for num in A_input:
    A[num] = 1

M = int(input())
M_input = input().split()
for num in M_input:
    if num in A:
        print(1)
    else:
        print(0)