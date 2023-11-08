from collections import deque

N = int(input())

for i in range(N):
    get_str = input()
    A = deque()
    B = deque()
    for ch in get_str:
        if ch == '(':
            A.append(ch)
        elif ch == ')':
            B.append(ch)
            if len(A) > 0:
                A.popleft()
                B.popleft()

    if len(A) > 0 or len(B) > 0:
        print("NO")
    else:
        print("YES")