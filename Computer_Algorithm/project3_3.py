import sys

N, E, K = map(int, sys.stdin.readline().split())

# G[v][0] : node의 정보들을 담고 있다. G[v][0][0] : d[v], G[v][0][1] : police 여부
# G[v][1] 부터 : G[v]의 neighbor와 edge의 weight 정보가 담겨있는 tuple들이 있다.
G = {i : [[sys.maxsize, 0, 0]] for i in range(1, N+1)}
not_sure = {i : 0 for i in range(1, N+1)}

for i in range(E):
    a, b, w = map(int, sys.stdin.readline().split())
    G[a].append((b, w))
    G[b].append((a, w))

for i in range(K):
    police_num = int(sys.stdin.readline())
    G[police_num][0][1] = 1
    not_sure.pop(police_num)

# 시작 node의 d[v] = 0
G[1][0][0] = 0
min_est_index = 0

while(len(not_sure) != 0):
    # pick the not-sure node u with the smallest estimate d[u]
    min_est_index = list(not_sure.keys())[0]
    for i in list(not_sure.keys()):
        if G[i][0][0] <= G[min_est_index][0][0]:
            min_est_index = i
        
    # change the value of d[v]
    for i in range(1, len(G[min_est_index])):
        v = G[min_est_index][i][0]
        w = G[min_est_index][i][1]
        
        # neighbor 중에서 police가 있을 수 있으니 이 경우를 제외
        if(G[v][0][1] == 1):
            continue
        else:
            G[v][0][0] = min(G[v][0][0], G[min_est_index][0][0] + w)
    
    # make u as sure
    not_sure.pop(min_est_index)

if G[N][0][0] != sys.maxsize:
    print(G[N][0][0])
else:
    print(-1)