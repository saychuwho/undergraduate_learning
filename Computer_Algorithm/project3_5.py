import sys

NAVER = 0
INFECTED = 1
D_V = 2

N, M = map(int, sys.stdin.readline().split())

# G[i][NAVER] : neighbor list. (neighbor, weight) tuple이 들어있다. 
# G[i][INFECTED] : infected bit 0(no) 1(yes), G[i][D_V] : d(v)
G = {i : [[], 0, sys.maxsize] for i in range(1, N+1)}
not_sure = {i : 0 for i in range(1, N+1)}

for i in range(M):
    A, B, W = map(int, sys.stdin.readline().split())
    G[A][NAVER].append((B, W))
    G[B][NAVER].append((A, W))

K = int(sys.stdin.readline())
infected = list(map(int, sys.stdin.readline().split()))

for k in infected:
    G[k][INFECTED] = 1
    not_sure.pop(k)

SAFE_HOUSE = int(sys.stdin.readline())

# 시작 node(safe house)의 d[v] = 0
G[SAFE_HOUSE][D_V] = 0
min_est_index = 0
total_weight = -1

if N > 1:
    # 다익스트라 알고리즘
    while(len(not_sure) != 0):
        min_est_index = list(not_sure.keys())[0]
        for i in list(not_sure.keys()):
            if G[i][D_V] <= G[min_est_index][D_V]:
                min_est_index = i

        for i in range(len(G[min_est_index][NAVER])):
            v = G[min_est_index][NAVER][i][0]
            w = G[min_est_index][NAVER][i][1]

            if G[v][INFECTED] == 1:
                continue
            else:
                G[v][D_V] = min(G[v][D_V], G[min_est_index][D_V] + w)
        
        not_sure.pop(min_est_index)

    total_weight = 0
    for i in range(1, N+1):
        if (G[i][INFECTED] == 0) and (G[i][D_V] != sys.maxsize):
            total_weight += G[i][D_V]
    if total_weight > 0:
        print(total_weight)
    else:
        print(-1)

else:
    print(-1)