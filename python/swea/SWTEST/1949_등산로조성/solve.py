import sys
sys.stdin = open("input.txt")
#############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

#############################################
def dfs(x, y, length = 1, check = False):
    global answer
    answer = max(answer, length)

    visited[x][y] = True

    for dir in range(4):
        nx = x + dx[dir]
        ny = y + dy[dir]

        if nx < 0 or nx >= N or ny < 0 or ny >= N or visited[nx][ny]:
            continue

        if graph[nx][ny] < graph[x][y]:
            dfs(nx, ny, length + 1, check)

        elif not check and graph[nx][ny] - K < graph[x][y]:
            temp = graph[nx][ny]
            graph[nx][ny] = graph[x][y] - 1
            dfs(nx, ny, length + 1, True)
            graph[nx][ny] = temp

    visited[x][y] = False


#############################################
T = int(input())

for test_case in range(1, T+1):
    N, K = map(int, input().split())
    graph = [list(map(int, input().split())) for _ in range(N)]

    visit = []
    max_h = 0
    for i in range(N):
        for j in range(N):
            if max_h < graph[i][j]:
                visit = [[i, j]]
                max_h = graph[i][j]

            elif max_h == graph[i][j]:
                visit.append([i, j])

    visited = [[False for _ in range(N)] for _ in range(N)]
    answer = 0

    for x, y in visit:
        dfs(x, y)

    print(f"#{test_case} {answer}")

