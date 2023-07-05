import sys
sys.stdin = open("input.txt")
#############################################
from collections import deque

dx = [0, -1, 0, 1, 0]
dy = [0, 0, 1, 0, -1]

#############################################
def set_bc(x, y, c, bc_num):
    visit = deque()
    visit.append([x, y, 0])
    visited = [[False for _ in range(10)] for _ in range(10)]
    visited[x][y] = True

    while visit:
        x, y, distance = visit.popleft()

        if distance > c:
            break

        graph[x][y].append(bc_num)
        for dir in range(1, 5):
            nx = x + dx[dir]
            ny = y + dy[dir]

            if nx < 0 or nx >= 10 or ny < 0 or ny >= 10 or visited[nx][ny]:
                continue

            visited[nx][ny] = True
            visit.append([nx, ny, distance + 1])


#############################################
def charge(a_bc, b_bc):
    global answer

    max_charge = 0
    for a in a_bc:
        for b in b_bc:
            if a == b:
                max_charge = max(max_charge, bc_power[a])

            else:
                max_charge = max(max_charge, bc_power[a] + bc_power[b])

    answer += max_charge


#############################################
T = int(input())

for test_case in range(1, T+1):
    m, a = map(int, input().split())

    graph = [[[0] for _ in range(10)] for _ in range(10)]

    a_move = [0] + list(map(int, input().split()))
    b_move = [0] + list(map(int, input().split()))

    bc_power = [0 for _ in range(a + 1)]

    for i in range(1, a+1):
        y, x, c, p = map(int, input().split())
        x -= 1
        y -= 1

        bc_power[i] = p
        set_bc(x, y, c, i)

    ax = 0
    ay = 0
    bx = 9
    by = 9

    answer = 0
    for i in range(m + 1):
        ax += dx[a_move[i]]
        ay += dy[a_move[i]]

        bx += dx[b_move[i]]
        by += dy[b_move[i]]

        charge(graph[ax][ay], graph[bx][by])

    print(f"#{test_case} {answer}")





