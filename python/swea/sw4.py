import heapq
import sys
input = sys.stdin.readline
#############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

#############################################
t = int(input())
INF = int(10e9)

for test_case in range(1,t+1):
    n = int(input())

    map_ = []
    for _ in range(n):
        map_.append(list(map(int, list(input().rstrip()))))

    distance = [[INF] * n for _ in range(n)]

    # 시작점의 거리는 0
    distance[0][0] = 0

    # 방문해야하는 노드를 힙으로 저장
    # 시작점은 cost = 0, x = 0, y = 0
    visit = []
    heapq.heappush(visit, [0, 0, 0])

    # 다익스트라 탐색
    while visit:
        cost, x, y = heapq.heappop(visit)

        # 모든 방향에 대해서
        for dir in range(4):
            nx = x + dx[dir]
            ny = y + dy[dir]

            # 영역 밖이면 무시
            if nx < 0 or nx >= n or ny < 0 or ny >= n:
                continue

            # 새로운 경로가 현재 탐색 경로보다 가까우면
            # 갱신 후 추가가
            if distance[nx][ny] > cost + map_[nx][ny]:
                distance[nx][ny] = cost + map_[nx][ny]
                heapq.heappush(visit, [cost + map_[nx][ny], nx, ny])

    print(f"#{test_case} {distance[n-1][n-1]}")