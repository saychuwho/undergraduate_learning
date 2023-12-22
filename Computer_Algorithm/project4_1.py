import sys
sys.setrecursionlimit(10**6)
sys.set_int_max_str_digits(10000000)

M = int(sys.stdin.readline())
L = list(map(int, sys.stdin.readline().split()))

L.sort() # O(nlog(n))

# O(n)
odd_L = []
even_L = []
for i, num in enumerate(L):
    if i % 2 == 0:
        odd_L.append(num)
    else:
        even_L.append(num)

# O(n)
A = 0
for i in range(len(odd_L)-1):
    tmp = odd_L[i+1] - odd_L[i]
    if A <= tmp:
        A = tmp

for i in range(len(even_L)-1):
    tmp = even_L[i+1] - even_L[i]
    if A <= tmp:
        A = tmp

tmp = abs(odd_L[-1] - even_L[-1])
if A <= tmp:
    A = tmp

tmp = abs(odd_L[0] - even_L[0])
if A <= tmp:
    A = tmp

print(A)