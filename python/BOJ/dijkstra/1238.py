import sys
input = sys.stdin.readline
import heapq
##############################################
# 초기 최대거리용 INF
INF = int(10e9)

n, m, x = map(int, input().split())

# 정방향, 역방향 간선 노드
# X -> 마을은 그냥 구해지지만,
# 마을 -> X는 다 따로 구해야 한다
# 근데 역방향 노드가 있으면 역방향으로 계산하면된다.
tree = [[] for _ in range(n+1)]
reverse = [[] for _ in range(n+1)]

for _ in range(m):
    a, b, cost = map(int, input().split())

    tree[a].append([b, cost])
    reverse[b].append([a, cost])


# 정방향 다익스트라
visit = []
heapq.heappush(visit, [0, x])

distance = [INF for _ in range(n+1)]
distance[x] = 0

while visit:
    cost, node = heapq.heappop(visit)

    for next_node, dis in tree[node]:
        if cost+dis < distance[next_node]:
            distance[next_node] = cost+dis
            heapq.heappush(visit, [cost + dis, next_node])

#################################################################
# 역방향 다익스트라
visit = []
heapq.heappush(visit, [0, x])

dis_reverse = [INF for _ in range(n + 1)]
dis_reverse[x] = 0

while visit:
    cost, node = heapq.heappop(visit)

    for next_node, dis in reverse[node]:
        if cost + dis < dis_reverse[next_node]:
            dis_reverse[next_node] = cost + dis
            heapq.heappush(visit, [cost + dis, next_node])

# 정답구하기
answer = -1

for i in range(1, n+1):
    answer = max(answer, distance[i] + dis_reverse[i])

print(answer)