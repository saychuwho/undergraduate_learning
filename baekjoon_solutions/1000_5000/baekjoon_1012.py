import sys
from collections import deque

sys.setrecursionlimit(10**6)

T = int(sys.stdin.readline())

UNVISITED = 0
IN_PROGRESS = 1
DONE = 2

for _ in range(T):
    M, N, K = map(int, sys.stdin.readline().split())
    #cabbage_map = [[0 for _ in range(M)] for _ in range(N)]
    cabbage = {}
    
    counter = 0

    for _ in range(K):
        x, y = map(int, sys.stdin.readline().split())
        #cabbage_map[x][y] = 1
        cabbage[(x,y)] = UNVISITED
    
    def DFS(u):
        cabbage[u] = IN_PROGRESS
        
        x, y = u
        tmp_up = (x-1, y) if x-1 >= 0 else 0
        tmp_down = (x+1, y) if x+1 <= M else 0
        tmp_left = (x, y-1) if y-1 >= 0 else 0
        tmp_right = (x, y+1) if y+1 <= N else 0
        tmp_list = [tmp_up, tmp_down, tmp_left, tmp_right]
        for v in tmp_list:
            if v == 0:
                continue
            elif v not in cabbage:
                continue
            elif cabbage[v] == UNVISITED:
                DFS(v)
        
        cabbage[u] = DONE

    while(len(cabbage) != 0):
        c = list(cabbage.keys())[0]
        DFS(c)
        
        tmp_cabbage = list(cabbage.keys())
        for tmp_c in tmp_cabbage:
            if cabbage[tmp_c] == DONE:
                cabbage.pop(tmp_c)

        counter += 1

    print(counter)    