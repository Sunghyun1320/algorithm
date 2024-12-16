import sys
sys.stdin = open("input.txt")
#############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
#############################################
def solve(graph, depth = 0, count = 0, core_count = 0):
    global answer, max_core
    if depth == count_cores:
        if core_count > max_core:
            max_core = core_count
            answer = count

        elif  core_count == max_core:
            answer = min(answer, count)
        return

    solve(graph, depth+1, count, core_count)

    for dir in range(4):
        new_count = 0
        check = True
        x, y = cores[depth]

        while True:
            x += dx[dir]
            y += dy[dir]

            if x < 0 or x >= N or y < 0 or y >= N:
                break

            if graph[x][y] != 0:
                check = False
                break

            graph[x][y] = 2
            new_count += 1

        if check:
            solve(graph, depth+1, count + new_count, core_count + 1)

        while True:
            x -= dx[dir]
            y -= dy[dir]

            if x < 0 or x >= N or y < 0 or y >= N:
                break

            if graph[x][y] != 2:
                break

            graph[x][y] = 0


#############################################
T = int(input())

for test_case in range(1, T+1):
    N = int(input())

    cell = [list(map(int, input().split())) for _ in range(N)]

    cores = []

    # 각 모서리에 있는 코어는 계산에서 제외
    for i in range(1, N-1):
        for j in range(1, N-1):
            if cell[i][j] == 1:
                cores.append([i, j])

    count_cores = len(cores)
    answer = int(1e9)
    max_core = 0

    solve(cell)

    print(f"#{test_case} {answer}")
