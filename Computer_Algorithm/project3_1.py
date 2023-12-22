import sys


N = int(sys.stdin.readline())

def algorithm():
    G = {1:[2,0,1]}
    depth = [[1]]
    visited = {1:1}

    for i, L_i in enumerate(depth):
        depth_append = []
        for u in L_i:
            if u not in G:
                tmp = 2*u
                if tmp > 99999:
                    tmp = 0
                G[u] = [tmp, u//3, int(str(u)[::-1])]
            for neighbor_u in G[u]:
                if neighbor_u not in visited:
                    visited[neighbor_u] = 1
                    depth_append.append(neighbor_u)
                if neighbor_u == N:
                    return i+1
        if len(depth_append) != 0:
            depth.append(depth_append)

    return -1

print(algorithm())
