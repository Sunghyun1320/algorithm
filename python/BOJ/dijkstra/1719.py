import sys
input = sys.stdin.readline
import heapq
#############################################
INF = int(1e9)
#############################################

n, m = map(int, input().split())

graph = [[] for _ in range(n+1)]

path = [[0 for _ in range(n+1)] for _ in range(n+1)]
distance = [[INF for _ in range(n+1)] for _ in range(n+1)]

for i in range(n+1):
    path[i][i] = INF
    distance[i][i] = 0


for _ in range(m):
    a, b, c = map(int, input().split())
    if a == b:
        continue

    graph[a].append([b, c])
    graph[b].append([a, c])

for i in range(1, n+1):
    visit = []
    for next_node, next_cost in graph[i]:
        distance[i][next_node] = next_cost
        path[i][next_node] = next_node
        heapq.heappush(visit, [next_cost, next_node, next_node])

    while visit:
        cost, node, frist = heapq.heappop(visit)

        for next_node, next_cost in graph[node]:
            if distance[i][next_node] <= cost + next_cost:
                continue

            distance[i][next_node] = cost + next_cost
            path[i][next_node] = frist
            heapq.heappush(visit, [cost+next_cost, next_node, frist])

for i in path[1:]:
    for j in i[1:]:
        if j == INF:
            print("-", end = " ")
            continue
        print(j, end=" ")

    print()
