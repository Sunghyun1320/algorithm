import sys
sys.stdin = open("input.txt")
#############################################
from copy import deepcopy
#############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
#############################################
def gravity(graph):
    for i in range(W):
        temp = []
        for j in range(H-1, -1, -1):
            if graph[j][i] != 0:
                temp.append(graph[j][i])
                graph[j][i] = 0

        j = H-1
        for num in temp:
            graph[j][i] = num
            j -= 1

    return graph


#############################################
def crash_block(w, graph):
    count = 0

    stack = []
    for i in range(H):
        if graph[i][w] != 0:
            stack.append([i, w])
            break

    while stack:
        x, y = stack.pop()
        if graph[x][y] == 0:
            continue

        if graph[x][y] == 1:
            count += 1
            graph[x][y] = 0
            continue

        for dir in range(4):
            for i in range(1, graph[x][y]):
                nx = x + dx[dir] * i
                ny = y + dy[dir] * i

                if nx < 0 or nx >= H or ny < 0 or ny >= W:
                    continue

                stack.append([nx, ny])

        count += 1
        graph[x][y] = 0

    graph = gravity(graph)
    return graph, count


#############################################
def dfs(graph, depth = 0, count = 0):
    if depth == N:
        global answer
        answer = max(answer, count)
        return

    for i in range(W):
        new_graph, new_count = crash_block(i, deepcopy(graph))
        dfs(deepcopy(new_graph), depth + 1, count + new_count)


#############################################
T = int(input())

for test_case in range(1, T+1):
    N, W, H = map(int, input().split())

    graph = [list(map(int, input().split())) for _ in range(H)]

    block_count = 0
    for i in range(H):
        for j in range(W):
            if graph[i][j] != 0:
                block_count += 1

    answer = 0

    dfs(deepcopy(graph))

    print(f"#{test_case} {block_count - answer}")

