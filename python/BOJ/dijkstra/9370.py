import sys
input = sys.stdin.readline
import heapq
############################################
T = int(input())

for test_case in range(T):
    n, m, t = map(int, input().split())
    s, g, h = map(int, input().split())

    graph = [[] for _ in range(n+1)]

    for _ in range(m):
        a, b, d = map(int, input().split())

        graph[a].append([b, d])
        graph[b].append([a, d])

    check_point = [int(input()) for _ in range(t)]

    # 다익스트라 연산
    visit = []
    # 거리와 노드, g,h노드 사용 여부를 저장
    heapq.heappush(visit, [0, s, False])
    distance = [[int(10e9), False] for _ in range(n+1)]
    distance[s] = [0, False]

    while visit:
        cost, node, check = heapq.heappop(visit)

        for next_node, dis in graph[node]:
            # 이번 경로가 g,h를 사용하는지 판단하는 변수
            # 이전에 g,h를 썼으면 True로 되어있음
            check_temp = check
            if (node == g and next_node == h) or (node == h and next_node == g):
                check_temp = True

            # 최단거리일시 최단거리 갱신후 heapq에 넣기
            if cost + dis < distance[next_node][0]:
                distance[next_node] = [dis+cost, check_temp]
                heapq.heappush(visit, [dis + cost, next_node, check_temp])

            # 같은 거리로 도달 했지만, 이전에 g,h경로를 사용하지 않았고, 현재 경로가 g,h를 사용했으면
            # True로 저장후 다시 heapq에 넣기
            if not distance[next_node][1] and check_temp and cost + dis == distance[next_node][0]:
                distance[next_node] = [dis + cost, check_temp]
                heapq.heappush(visit, [dis + cost, next_node, check_temp])

    answer = []
    for i in check_point:
        if distance[i][1]:
            answer.append(i)

    answer.sort()
    print(*answer)
