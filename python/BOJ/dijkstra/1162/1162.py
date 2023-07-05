import sys
input = sys.stdin.readline
import heapq
######################################################
INF = int(sys.maxsize)
######################################################
n, m, k = map(int, input().split())

city = [[] for _ in range(n+1)]

for _ in range(m):
    a, b, cost = map(int, input().split())
    if a == b:
        continue

    city[a].append([b, cost])
    city[b].append([a, cost])

distance = [[INF for _ in range(k+1)] for _ in range(n+1)]
distance[1] = [0 for _ in range(k+1)]

visit = []
heapq.heappush(visit, [0, 1, 0])

while visit:
    new_cost, node, cover = heapq.heappop(visit)

    # 이거 안해주면 시간초과..... 왜지?
    # 시간을 줄일 수 있는건 맞는데 이걸 어떻게 떠올리냐....
    if distance[node][cover] < new_cost:
        continue

    if cover + 1 <= k:
        for next_node, cost in city[node]:
            if distance[next_node][cover + 1] > new_cost:
                distance[next_node][cover + 1] = new_cost
                heapq.heappush(visit, [new_cost, next_node, cover + 1])

    for next_node, cost in city[node]:
        if distance[next_node][cover] <= new_cost + cost:
            continue

        distance[next_node][cover] = new_cost + cost
        heapq.heappush(visit, [new_cost + cost, next_node, cover])

ans = INF
for i in range(k+1):
    ans = min(ans, distance[n][i])

print(ans)
