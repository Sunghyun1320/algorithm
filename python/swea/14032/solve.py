import sys
sys.stdin = open("input.txt")
from collections import deque
###########################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
###########################################
t = int(input())

for test_case in range(1, t+1):
    n = int(input())

    room = [list(map(int, input().split())) for _ in range(n)]
    visited = [[False for _ in range(n)] for _ in range(n)]
    max_len = -1
    answer = None

    for i in range(n):
        for j in range(n):
            visit = deque()
            visit.append([i, j])
            visited[i][j] = True

            check_left = False
            check_right = True

            while visit:
                if not check_right and not check_left:
                    break

                if check_right:
                    x, y = visit[-1]

                    check_right = False

                    for dir in range(4):
                        nx = x + dx[dir]
                        ny = y + dy[dir]

                        if nx < 0 or nx >= n or ny < 0 or ny >= n:
                            continue

                        if room[nx][ny] == room[x][y] + 1:
                            visit.append([nx, ny])
                            check_right = True
                            break

                if check_left:
                    x, y = visit[0]
                    check_left = False

                    for dir in range(4):
                        nx = x + dx[dir]
                        ny = y + dy[dir]

                        if nx < 0 or nx >= n or ny < 0 or ny >= n:
                            continue

                        if room[nx][ny] == room[x][y] - 1:
                            visit.appendleft([nx, ny])
                            check_left = True

            if len(visit) == max_len:
                if answer > room[visit[0][0]][visit[0][1]]:
                    answer = room[visit[0][0]][visit[0][1]]

            if len(visit) > max_len:
                answer = room[visit[0][0]][visit[0][1]]
                max_len = len(visit)

    print(f"#{test_case} {answer} {max_len}")