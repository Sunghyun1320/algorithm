import sys
input = sys.stdin.readline
import heapq
###############################################
# 입력은 여러개의 테스트 케이스로 이루어 져있으므로 반복
while True:
    # m, n 입력받기
    m, n = map(int, input().split())
    # 만약 둘 다 0이면 종료조건이므로 반복  종료
    if m == 0 and n == 0:
        break

    # 집 구조 저장할 그래프
    graph = [[] for _ in range(m)]

    # 현재 소모중인 전력
    sum_distance = 0

    # 간선 정보 입력받기
    for _ in range(n):
        x, y, z = map(int, input().split())

        graph[x].append([y, z])
        graph[y].append([x, z])

        sum_distance += z

    # 집이 MST에 포함되었는지 체크하는 visited 리스트
    visited = [False for _ in range(m)]
    # 간선의 최소값을 가져올 최소 힙
    heap = []
    # 시작노드 입력하기
    heapq.heappush(heap, [0, 0])
    # MST에 포함된 집의 개수
    count = 0
    # MST로 소모하는 최소 전력
    sum_cost = 0

    # MST구하기
    while True:
        # 집을 모두 포함시켰으면 종료
        if count == m:
            break

        cost, node = heapq.heappop(heap)

        # 방문노드이면 사이클이 형성되므로 패스
        if visited[node]:
            continue

        # 현재 노드 방문처리
        visited[node] = True
        # 집 개수 추가
        count += 1
        # 비용 갱신
        sum_cost += cost

        # 새로 연결된 집에서 연결된 간선 정보 더하기
        for next_node, new_cost in graph[node]:
            if visited[next_node]:
                continue

            heapq.heappush(heap, [new_cost, next_node])

    # 절약 비용은 현재소모 전력 - 최소소모 전력
    print(sum_distance - sum_cost)