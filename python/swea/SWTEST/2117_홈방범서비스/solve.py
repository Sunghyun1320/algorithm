import sys
sys.stdin = open("input.txt")
#############################################
from collections import deque

dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
#############################################
def bfs(x, y):
    global answer
    visited = [[False for _ in range(N)] for _ in range(N)]
    start = deque()
    start.append([x, y, 0])
    visited[x][y] = True

    count = 0
    new_distance = 1
    while start:
        x, y, distance = start.popleft()

        if new_distance == distance:
            need_cost = distance ** 2 + (distance - 1) ** 2
            get_cost = M * count

            if need_cost <= get_cost:
                answer = max(answer, count)

        if graph[x][y] == 1:
            count += 1

        new_distance = distance + 1

        for dir in range(4):
            nx = x + dx[dir]
            ny = y + dy[dir]

            if nx < 0 or nx >= N or ny < 0 or ny >= N or visited[nx][ny]:
                continue

            visited[nx][ny] = True
            start.append([nx, ny, new_distance])

    need_cost = distance ** 2 + (distance + 1) ** 2
    get_cost = M * count

    if need_cost <= get_cost:
        answer = max(answer, count)


#############################################
T = int(input())

for test_case in range(1, T+1):
    N, M = map(int, input().split())

    graph = [list(map(int, input().split())) for _ in range(N)]

    answer = 0
    for i in range(N):
        for j in range(N):
            bfs(i, j)

    print(f"#{test_case} {answer}")

