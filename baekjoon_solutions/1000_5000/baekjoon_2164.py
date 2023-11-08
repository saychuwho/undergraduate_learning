from collections import deque

N = int(input())

Q = deque()
for i in range(1, N+1):
    Q.append(i)

counter = 1
while(len(Q) > 1):
    if counter % 2 != 0:
        Q.popleft()
    else:
        tmp_num = Q.popleft()
        Q.append(tmp_num)
    counter += 1

print(Q.popleft())