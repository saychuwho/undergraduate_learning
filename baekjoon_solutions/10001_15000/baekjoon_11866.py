from collections import deque

N, K = map(int, input().split())

queue = deque()
result_str = "<"
counter = 1

for i in range(1,N+1):
    queue.append(i)

while(len(queue) != 0):
    if counter % K == 0:
        result_str += str(queue.popleft()) + ", "
    else:
        queue.append(queue.popleft())
    counter += 1

result_str = result_str[:-2] + ">"
print(result_str)