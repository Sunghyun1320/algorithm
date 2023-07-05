dx = [-1, -1, 0]
dy = [0, -1, -1]


def check(depth = 0):
    if depth == n * m:
        global count
        count += 1
        return

    x = depth // n
    y = depth % n

    temp = 0
    for dir in range(3):
        nx = x + dx[dir]
        ny = y + dy[dir]

        if nx < 0 or nx >= m or ny < 0 or ny >= n:
            continue

        if graph[nx][ny] == 1:
            temp += 1

    if temp == 3:
        check(depth + 1)

    else:
        graph[x][y] = 1
        check(depth + 1)
        graph[x][y] = 0
        check(depth + 1)


n, m = map(int, input().split())

graph = [[0 for _ in range(n)] for _ in range(m)]

count = 0

check()

print(count)

