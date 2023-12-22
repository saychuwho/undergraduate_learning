import sys

N = int(sys.stdin.readline())

A = {0:{1:0, 3:0, 5:0},-1:{1:0,3:0,5:0}, -2:{1:0,3:0,5:0}, -3:{1:0,3:0,5:0}, -4:{1:0,3:0,5:0},
     1:{1:1, 3:0, 5:0}, 3:{1:0, 3:1, 5:0}, 5:{1:1, 3:0, 5:1}}


for num in range(2, N+1):
    if num in A:
        continue
    else:
        A[num] = {}
        A[num][1] = A[num-1][3] + A[num-1][5]
        A[num][3] = A[num-3][1] + A[num-3][5]
        A[num][5] = A[num-5][1] + A[num-5][3]

result = list(A[N].values())

if sum(result) == 0:
    print(-1)
else:
    print(sum(result))
