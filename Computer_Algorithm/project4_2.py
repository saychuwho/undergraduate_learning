import sys
sys.setrecursionlimit(10**6)
sys.set_int_max_str_digits(10000000)

M = [[0 for _ in range(50)] for _ in range(50)]

B, C = map(int, sys.stdin.readline().split())

G = [[0 for _ in range(B+1)] for _ in range(B+1)]

house = {}
house_list = []

start_point = tuple(map(int, sys.stdin.readline().split()))

# 0 : start_point, 1 ~ B : 지어야 할 집들
house[start_point] = 0
house_list.append(start_point)
M[start_point[0]][start_point[1]] = 1

# 집을 짓는 곳 규정
for i in range(B):
    x, y = map(int, sys.stdin.readline().split())
    M[x][y] = 1
    house[(x,y)] = i+1
    house_list.append((x,y))


# 장애물 규정
for _ in range(C):
    x, y = map(int, sys.stdin.readline().split())
    M[x][y] = 2

# BFS : h에서 나머지 node들 간의 거리를 구한다.

for h in list(house.keys()):

    L = [[] for _ in range(2500)]
    L[0].append(h)
    visited = {}
    visited[h] = 1

    for i in range(2500):
        for u in L[i]:
            x, y = u
            tmp_up = (x-1, y) if (x - 1 >= 0) else 0
            tmp_down = (x+1, y) if (x+1 < 50) else 0
            tmp_left = (x, y-1) if (y-1 >= 0) else 0
            tmp_right = (x, y+1) if (y+1 < 50) else 0
            tmp_list = [tmp_up, tmp_down, tmp_left, tmp_right]

            for v in tmp_list:
                if v == 0:
                    continue
                if M[v[0]][v[1]] == 2:
                    continue
                else:
                    if v not in visited:
                        visited[v] = 1
                        L[i+1].append(v)
            
            # h와 edge들 간의 거리를 저장
            for u in L[i]:
                # 집을 지어야 할 곳이면
                if M[u[0]][u[1]] == 1:
                    G[house[h]][house[u]] = i
            

# prim's algorithm
MST = []

reached = {}
not_reached = house.copy()
K = [sys.maxsize for _ in range(B+1)]
K[0] = 0
reached[start_point] = 1
P = {}
P[0] = 0

while(len(not_reached) != 0):

    # pick smallest k[v] in not_reached
    min_u = list(not_reached.keys())[0]
    min_u_k = sys.maxsize
    for u in list(not_reached.keys()):
        if K[house[u]] < min_u_k:
            min_u = u
            min_u_k = K[house[min_u]]

    # u의 neighbor들의 k를 update
    for v, d in enumerate(G[house[min_u]]):

        if house_list[v] in reached:
            continue
        
        if d == 0:
            continue

        tmp_k = K[v]
        K[v] = min(tmp_k, d)

        if tmp_k != K[v]:
            P[v] = house[min_u]

    not_reached.pop(min_u)
    reached[min_u] = 1
    MST.append((P[house[min_u]], house[min_u]))

# edge들의 합 구하기
length = 0
for x, y in MST:
    length += G[x][y]

print(length)