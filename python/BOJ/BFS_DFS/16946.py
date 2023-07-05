import sys
from collections import deque
from copy import deepcopy
input = sys.stdin.readline
##########################################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
##########################################################
n, m = map(int, input().split())

map_graph = [list(map(int, list(input().rstrip()))) for _ in range(n)]

answer = deepcopy(map_graph)

same_zero_area = [0, 0]

num = 2

# 모든 0들을 하나의 덩어리로 뭉치기, 번호는 덩어리 구분,
# same_zero_area에 번호 인덱스로 접근하면 덩어리 크기가 나옴
for i in range(n):
    for j in range(m):
        # 이동가능한 칸이 나오면 해당 칸을 기준으로 bfs로 같은 덩어리를 찾음
        if map_graph[i][j] == 0:
            map_graph[i][j] = num
            same_zero_area.append(1)

            visit = deque()
            visit.append((i, j,))

            while visit:
                x, y = visit.popleft()

                for dir in range(4):
                    nx = x + dx[dir]
                    ny = y + dy[dir]

                    if nx < 0 or nx >= n or ny < 0 or ny >= m or map_graph[nx][ny] != 0:
                        continue

                    map_graph[nx][ny] = num
                    same_zero_area[num] += 1

                    visit.append((nx, ny,))

            num += 1

# for i in map_graph:
#     print(i)
#
# print(same_zero_area)
##########################################################
for i in range(n):
    for j in range(m):
        if map_graph[i][j] != 1:
            continue

        count = 1

        check = {}

        for dir in range(4):
            nx = i + dx[dir]
            ny = j + dy[dir]

            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue

            if check.get(map_graph[nx][ny], 0):
                continue

            check[map_graph[nx][ny]] = 1
            count += same_zero_area[map_graph[nx][ny]]

        answer[i][j] = count % 10

for i in answer:
    print("".join(list(map(str, i))))




