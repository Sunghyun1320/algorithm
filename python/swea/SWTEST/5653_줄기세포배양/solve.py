import sys
sys.stdin = open("input.txt")
#############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
#############################################
def difuze():
    alive_temp = []
    unalive_temp = []

    # 살아있는 세포들 증식
    while alive:
        # 현재 살아있는 세포들
        x, y = alive.pop()

        # 4가지 방향에 대해서
        for dir in range(4):
            nx = x + dx[dir]
            ny = y + dy[dir]

            # 빈칸이면 바로 증식
            if graph[nx][ny] == 0:
                # 현재칸의 생명력으로 생명력과 시간을 가지며 현재 만든놈이라고 False처리
                graph[nx][ny] = [graph[x][y][0], graph[x][y][0], False]
                # 임시로 활성화 안된 세포에 추가
                unalive_temp.append([nx, ny])
                continue

            # 이전에 만들어진 놈이면 증식 안함
            if graph[nx][ny][2]:
                continue

            # 이번에 증식했지만, 내 생명력이 더 크면 갱신
            # 하지만 이전에 추가 되어있으므로 추가하진 않음
            if graph[nx][ny][0] < graph[x][y][0]:
                graph[nx][ny] = [graph[x][y][0], graph[x][y][0], False]
                continue

        # 시간 감소 후, 생명력이 남아있으면 임시로 채움
        graph[x][y][1] -= 1
        if graph[x][y][1] > 0:
            alive_temp.append([x, y])

    # 활성화 안 된 세포들에 대해서
    while unalive:
        x, y = unalive.pop()

        # 시간 감소 후 살아난 세포에 추가
        graph[x][y][1] -= 1
        if graph[x][y][1] == 0:
            alive_temp.append([x, y])
            graph[x][y][1] = graph[x][y][0]

        # 아직 시간이 남아있으면 이번에 증식된거처럼 처리후
        # 임시로 채움
        else:
            graph[x][y][2] = False
            unalive_temp.append([x, y])

    # 임시로 나온 비활성화 세포들에 대해서
    for x, y in unalive_temp:
        # 이전에 처리가 되었으면 넘어감
        if graph[x][y][2]:
            continue

        # 처리가 안됐으면 처리하고, 추가해 줌
        graph[x][y][2] = True
        unalive.append([x, y])

    # 그리고 살아있는 세포는 그대로 추가
    while alive_temp:
        alive.append(alive_temp.pop())


#############################################
T = int(input())

for test_case in range(1, T+1):
    N, M, K = map(int, input().split())

    graph = [[0 for _ in range(2*K + M)] for _ in range(K)]

    for _ in range(N):
        graph.append([0 for _ in range(K)] + list(map(int, input().split())) + [0 for _ in range(K)])

    for _ in range(K):
        graph.append([0 for _ in range(2*K + M)])

    N += 2 * K
    M += 2 * K

    unalive = []
    alive = []

    for i in range(N):
        for j in range(M):
            if graph[i][j] != 0:
                graph[i][j] = [graph[i][j], graph[i][j], True]
                unalive.append([i, j])

    for _ in range(K):
        difuze()

    print(f"#{test_case} {len(unalive) + len(alive)}")