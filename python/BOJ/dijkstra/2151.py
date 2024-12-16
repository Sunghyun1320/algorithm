import sys
input = sys.stdin.readline
from collections import deque
########################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
########################################
n = int(input())

room = [list(input().rstrip()) for _ in range(n)]

door = []
for i in range(n):
    for j in range(n):
        if room[i][j] == "#":
            door.append([i, j])

visit = deque()
visited = [[False for _ in range(n)] for _ in range(n)]
x, y = door[0]
visited[x][y] = True

for dir in range(4):
    nx = x + dx[dir]
    ny = y + dy[dir]

    if nx < 0 or nx >= n or ny < 0 or ny >= n or room[nx][ny] == "*" or visited[nx][ny]:
        continue

    visited[nx][ny] = True
    visit.append([dir, nx, ny])

while visit:
    dir, x, y = visit.popleft()

    nx = x + dx[dir]
    ny = y + dy[dir]

    if nx < 0 or nx >= n or ny < 0 or ny >= n or room[nx][ny] == "*" or visited[nx][ny]:
        continue




