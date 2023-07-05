import sys
from collections import deque
import heapq
input = sys.stdin.readline
################################################################
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]

################################################################
n, m = map(int, input().split())

island = [list(map(int, input().split())) for _ in range(n)]

count_island = 0

# 각 섬들과 다른 섬들을 이어주는 경로를 저장하는 변수
load = {}

################################################################
island_char = ord("A")

# 모든 섬들을 구분하기 'A' ~ 'F'
for i in range(n):
    for j in range(m):
        if island[i][j] == 0:
            island[i][j] = '0'
            continue
        # 섬을 찾으면
        if island[i][j] == 1:
            # 섬의 개수 추가
            count_island += 1

            # 해당섬의 명칭 변경
            island[i][j] = chr(island_char)

            # 해당 섬 추가
            load[chr(island_char)] = {}

            # BFS로 같은 섬들 전부 같은 명칭으로 변경
            visit = deque()
            visit.append((i, j,))

            while visit:
                x, y = visit.pop()

                for dir in range(4):
                    nx = x + dx[dir]
                    ny = y + dy[dir]

                    if nx < 0 or nx >= n or ny < 0 or ny >= m or island[nx][ny] != 1:
                        continue

                    island[nx][ny] = chr(island_char)
                    visit.append((nx, ny,))

            # 다른 섬들은 다른 알파벳
            island_char += 1


# for i in island:
#     print(i)
#
# print("#############################")
################################################################
# 가로방향으로 놓을 수 있는 모든 다리 체크
for i in range(n):
    s = False
    len_load = 0
    for j in range(1, m):
        # 가로방향 체크시 섬이 바다와 맞닿으면 시작점은 해당 섬
        if str(island[i][j-1]).isalpha() and island[i][j] == '0':
            s = island[i][j-1]

        # 시작섬이 있고, 해당칸이 바다이면 다리길이 늘리기
        if s and island[i][j] == '0':
            len_load += 1

        # 시작섬이 있고, 다른 섬에 도착했을 때
        if s and str(island[i][j]).isalpha():
            # 다리의 길이가 2 이상이고,
            if len_load >= 2 and island[i][j] != s:
                # 해당 섬까지의 경로가 최단경로이면 갱신
                # 이전에 탐색되지 않은 경로면 그냥 추가
                if load[s].get(island[i][j], 11) > len_load:
                    load[s][island[i][j]] = len_load
                    load[island[i][j]][s] = len_load

                    # 그 다음 다시 다리길이 초기화, 시작섬 삭제
                    len_load = 0
                    s = False

            # 다리길이가 2이상이 안되면 시작섬 삭제, 다리길이 초기화
            else:
                len_load = 0
                s = False

            # 하나의 행에 2개의 다리가 놓일 수 있으므로 초기화
            len_load = 0
            s = False

# 세로방향 다리 체크
for j in range(m):
    s = False
    len_load = 0
    for i in range(1, n):
        # 세로방향 체크시 섬이 바다와 맞닿으면 시작점은 해당 섬
        if str(island[i - 1][j]).isalpha() and island[i][j] == '0':
            s = island[i-1][j]

        if s and island[i][j] == '0':
            len_load += 1

        # 시작섬이 있고, 다른 섬에 도착했을 때
        if s and str(island[i][j]).isalpha():
            #  다리 길이가 2 이상이고
            if len_load >= 2 and island[i][j] != s:
                # 이전에 탐색한 다리길이 보다 짧으면 거리 갱신
                # 경로와 열 추가 행, 열은 양수 음수로 구분
                if load[s].get(island[i][j], 11)> len_load:
                    load[s][island[i][j]] = len_load
                    load[island[i][j]][s] = len_load
                    len_load = 0
                    s = False

            # 다리길이가 1이면 길이 초기화, 시작섬 삭제
            else:
                len_load = 0
                s = False

            # 하나의 행에 2개의 다리가 놓일 수 있으므로 초기화
            len_load = 0
            s = False
#
# for i in load.items():
#     print(i)

################################################################
# 만들어진 그래프에서 최소신장 트리 찾기
cost = []
heapq.heappush(cost, (0, 'A',))
visited = {}

answer = 0
i = 0
while True:
    if i == count_island and len(visited) == count_island:
        print(answer)
        break

    if not cost:
        print(-1)
        break

    load_cost, node = heapq.heappop(cost)
    if visited.get(node, False):
        continue

    visited[node] = True
    answer += load_cost

    for key, values in load[node].items():
        if not visited.get(key, False):
            heapq.heappush(cost, (values, key,))

    i += 1









