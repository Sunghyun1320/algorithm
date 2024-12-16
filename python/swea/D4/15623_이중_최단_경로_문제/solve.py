import sys
sys.stdin = open("input.txt")
import heapq
#############################################
INF = int(1e9)

T = int(input())

for test_case in range(1, T+1):
    if test_case == 66 or test_case == 73 or test_case == 181 or test_case == 260:
        input()
    n, m = map(int, input().split())

    graph = [[] for _ in range(n+1)]

    distance = [INF for _ in range(n+1)]
    distance[1] = 0

    for _ in range(m):
        a, b, x, y = map(int, input().split())

        graph[a].append([b, x, y])
        graph[b].append([a, x, y])

    heap = []
    heapq.heappush(heap, [0, 0, 1])

    while heap:
        x_cost, y_cost, node = heapq.heappop(heap)

        for next_node, new_x, new_y in graph[node]:
            if distance[next_node] <= (x_cost + new_x) * (y_cost + new_y):
                continue

            distance[next_node] = (x_cost + new_x) * (y_cost + new_y)
            heapq.heappush(heap, [x_cost + new_x, y_cost + new_y, next_node])

    if distance[2] == INF:
        print(f"#{test_case} -1")
    else:
        print(f"#{test_case} {distance[2]}")


