dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

# 값 입력받기
n, *persent = map(int, input().split())

# 계산하기
def cal(depth, n, x, y, per=1):
    # 확률이 0이면 리턴
    if per == 0:
        return

    # 최대깊이에서 확률 더해주기
    if depth == n:
        global answer
        answer += per
        return

    # 4가지 방향에 대해서
    for dir in range(4):
        nx = x + dx[dir]
        ny = y + dy[dir]

        # 방문 했으면 pass
        if visited[nx][ny]:
            continue

        # 방문 처리후 다음 방향 정하기
        visited[nx][ny] = True
        cal(depth+1, n, nx, ny, per*persent[dir])
        visited[nx][ny] = False


visited = [[False for _ in range(n*2+1)] for _ in range(n*2+1)]
visited[n][n] = True
answer = 0

cal(0, n, n, n)

# 확률이 %로 계산되었으므로 깊이만큼 100으로 나누기
for i in range(n):
    answer /= 100

print(answer)