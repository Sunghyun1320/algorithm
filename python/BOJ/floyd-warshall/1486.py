import sys
input = sys.stdin.readline
import heapq
######################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

INF = int(1e9)
######################################
n, m, t, d = map(int, input().split())

graph = [list(input()) for _ in range(n)]

# 알파벳에 해당하는 숫자로 바꾸기
for i in range(n):
    for j in range(m):
        if graph[i][j].isupper():
            graph[i][j] = ord(graph[i][j]) - ord('A')

        else:
            graph[i][j] = ord(graph[i][j]) - ord('a') + 26


# 다익스트라 시작
distance = [[INF for _ in range(m)] for _ in range(n)]
distance[0][0] = 0
heap = []
heapq.heappush(heap, [0, 0, 0])

# 호텔 ~ 지점까지 걸리는 시간
while heap:
    cost, x, y = heapq.heappop(heap)

    for dir in range(4):
        nx = x + dx[dir]
        ny = y + dy[dir]

        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue

        if graph[nx][ny] - graph[x][y] > t or graph[x][y] - graph[nx][ny] < -t:
            continue

        if graph[nx][ny] <= graph[x][y]:
            new_cost = cost + 1
        else:
            new_cost = cost + ((graph[nx][ny] - graph[x][y]) ** 2)

        if distance[nx][ny] > new_cost:
            distance[nx][ny] = new_cost
            heapq.heappush(heap, [new_cost, nx, ny])

# 2번째 다익스트라 시작
distance2 = [[INF for _ in range(m)] for _ in range(n)]
distance2[0][0] = 0
heap = []
heapq.heappush(heap, [0, 0, 0])

# 지점 ~ 호텔까지 돌아오는 거리
while heap:
    cost, x, y = heapq.heappop(heap)

    for dir in range(4):
        nx = x + dx[dir]
        ny = y + dy[dir]

        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue

        if graph[nx][ny] - graph[x][y] > t or graph[x][y] - graph[nx][ny] < -t:
            continue

        if graph[nx][ny] >= graph[x][y]:
            new_cost = cost + 1
        else:
            new_cost = cost + ((graph[nx][ny] - graph[x][y]) ** 2)

        if distance2[nx][ny] > new_cost:
            distance2[nx][ny] = new_cost
            heapq.heappush(heap, [new_cost, nx, ny])

answer = 0
# 모든 지점에 대해서
for i in range(n):
    for j in range(m):
        # d이상의 시간이 걸리면 패스
        if distance[i][j] + distance2[i][j] > d:
            continue

        # 가장 높은 지점 갱신
        answer = max(answer, graph[i][j])

# 출력
print(answer)
