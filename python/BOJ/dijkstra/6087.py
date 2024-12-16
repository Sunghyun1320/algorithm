import sys
input = sys.stdin.readline
import heapq
##############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
##############################################
INF = int(1e9)
##############################################
w, h = map(int, input().split())

graph = [list(input().rstrip()) for _ in range(h)]

check_point = []
for i in range(h):
    for j in range(w):
        if graph[i][j] == 'C':
            check_point.append([i, j])
            graph[i][j] = '.'

heap = []
x = check_point[0][0]
y = check_point[0][1]

graph[x][y] = 0

# 시작점에서 상하좌우는 모두 0개로 접근 가능
for dir in range(4):
    i = 1
    while True:
        nx = x + dx[dir]*i
        ny = y + dy[dir]*i

        # 범위 이탈이나 벽만나면 멈춤
        if nx < 0 or nx >= h or ny < 0 or ny >= w or graph[nx][ny] == "*":
            break

        # 거울의 개수와 방향, 위치를 저장
        graph[nx][ny] = 0
        heapq.heappush(heap, [0, dir, nx, ny])
        i += 1

# 다익스트라 시작
while heap:
    cost, diriction, x, y = heapq.heappop(heap)

    # diriction +1 or -1이 꺾이는 방향
    for k in [-1, 1]:
        dir = (diriction + k) % 4

        # 해당 방향으로 쭉 나아감
        i = 1
        while True:
            nx = x + dx[dir] * i
            ny = y + dy[dir] * i

            # 범위 이탈하거나 벽만나면 멈춤
            if nx < 0 or nx >= h or ny < 0 or ny >= w or graph[nx][ny] == "*":
                break

            # 처음 도착하거나 더 적은 거울 개수로 올 수 있으면 heap에 추가
            if graph[nx][ny] == "." or graph[nx][ny] > cost + 1:
                graph[nx][ny] = cost + 1
                heapq.heappush(heap, [cost + 1, dir, nx, ny])

            i += 1

# 출력
x, y = check_point[1]
print(graph[x][y])



