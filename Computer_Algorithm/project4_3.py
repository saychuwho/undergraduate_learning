import sys
sys.setrecursionlimit(10**6)
sys.set_int_max_str_digits(10000000)

def BFS(graph, start, target, before_node):
    visited = [False] * len(graph)
    q = []
    q.append(start)
    visited[start] = True

    while q:
        u = q.pop(0)
        for node in range(len(graph[u])):
            if visited[node] is False and graph[u][node] > 0:
                q.append(node)
                visited[node] = True
                before_node[node] = u

    return True if visited[target] else False

def ford_fulkerson(graph, source, sink):
    before_node = [-1 for _ in range(len(graph))]
    max_flow = 0

    while BFS(graph, source, sink, before_node):
        path_min_flow = sys.maxsize
        v = sink

        # find min flow in path
        while v != source:
            path_min_flow = min(path_min_flow, graph[before_node[v]][v])
            v = before_node[v]
        
        max_flow += path_min_flow
        v = sink

        # update residual graph : increase_flow + making residual graph
        while v != source:
            u = before_node[v]
            graph[u][v] -= path_min_flow
            graph[v][u] += path_min_flow
            v = before_node[v]
    
    return max_flow


N, M = map(int, sys.stdin.readline().split())

G = [[0 for _ in range(N)] for _ in range(N)]

for _ in range(M):
    a, b, c = map(int, sys.stdin.readline().split())
    G[a][b] = c

source = 0
sink = N-1

print(ford_fulkerson(G, source, sink))