import sys
input = sys.stdin.readline
import heapq
##########################################
INF = int(1e9)
##########################################
n = int(input())
m = int(input())

graph = [[] for _ in range(n+1)]

for _ in range(m):
    a, b, c = map(int, input().split())

    graph[a].append([b, c])

start, goal = map(int, input().split())

visit = []
distance = [INF for _ in range(n+1)]
distance[start] = 0
ans_path = [0 for _ in range(n+1)]
heapq.heappush(visit, [0, start])

while visit:
    cost, node = heapq.heappop(visit)

    # 이게 뭐지??
    if distance[node] < cost:
        continue

    for next_node, next_cost in graph[node]:
        if distance[next_node] < cost + next_cost:
            continue

        if distance[next_node] == cost + next_cost:
            continue

        distance[next_node] = cost + next_cost
        ans_path[next_node] = node
        heapq.heappush(visit, [cost+next_cost, next_node])


print(distance[goal])
path = []
node = goal
while True:
    if node == start:
        path.append(start)
        break
    path.append(node)
    node = ans_path[node]

print(len(path))
print(*path[::-1])

