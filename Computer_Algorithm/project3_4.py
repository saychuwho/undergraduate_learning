import sys

sys.setrecursionlimit(10**6)

list_index = lambda x : x-1

N = int(sys.stdin.readline())

T = {i:[] for i in range(1,N+1)}
animal_type = list(map(int, sys.stdin.readline().split()))

for i in range(N-1):
    parent, child = map(int, sys.stdin.readline().split())
    T[parent].append(child)

R = {i : {} for i in range(1, N+1)}

def algorithm(cur_node, cur_sheep, cur_wolf, can_visit):
    node_sheep = cur_sheep + 1 if animal_type[list_index(cur_node)] == 0 else cur_sheep
    node_wolf = cur_wolf + 1 if animal_type[list_index(cur_node)] == 1 else cur_wolf

    tmp_sheep = node_sheep

    if node_wolf >= node_sheep:
        R[cur_node][(cur_sheep, cur_wolf)] = tmp_sheep
        return tmp_sheep
    
    for next_node in can_visit:
        next_can_visit = can_visit[:]
        next_can_visit.remove(next_node)
        next_can_visit += T[next_node]
        ret_sheep = 0
        if (node_sheep, node_wolf) in R[next_node]:
            ret_sheep = R[next_node][(node_sheep, node_wolf)]
        else: 
            ret_sheep = algorithm(next_node, node_sheep, node_wolf, next_can_visit)
        tmp_sheep = max(tmp_sheep, ret_sheep)

    R[cur_node][(cur_sheep, cur_wolf)] = tmp_sheep
    return tmp_sheep

first_can_visit = T[1][:]

ret_sheep = algorithm(1, 0, 0, first_can_visit)

print(ret_sheep)