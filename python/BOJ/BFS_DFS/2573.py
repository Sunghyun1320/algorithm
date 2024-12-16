# clear pypy3
import sys
input = sys.stdin.readline
from copy import deepcopy
from collections import deque

###############################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
###############################################
# 빙산이 녹은 결과를 반환하는 함수
def Melt_ice():
    # 새로 저장된 녹은 얼음
    new_ice = [[0 for _ in range(m)] for _ in range(n)]

    # 모든 칸에 대해서
    for x in range(n):
        for y in range(m):
            # 바다이면 수행 안함
            if ice_map[x][y] == 0:
                continue

            # 주변의 바다인 칸의 개수
            count = 0
            # 주변 4칸에 대해서
            for dir in range(4):
                nx = x + dx[dir]
                ny = y + dy[dir]

                # 범위 벗어나면 체크 안함
                if nx < 0 or nx >= n or ny < 0 or ny >= m:
                    continue

                # 바다이면 개수 추가
                if ice_map[nx][ny] == 0:
                    count += 1

            # 새로 녹은 배열에 녹은 얼음의 크기를 저장
            # 만약 음수면 0으로 저장
            new_ice[x][y] = ice_map[x][y] - count if ice_map[x][y] > count else 0

    return new_ice


###############################################
# 빙산의 개수를 반환하는 함수
def Count_ice():
    # 기존의 얼음에 영향을 미치지 않기 위한 deepcopy
    new_ice = deepcopy(ice_map)

    # 얼음 덩어리의 개수
    count_ice = 0

    # 모든칸에 대해서
    for x in range(n):
        for y in range(m):
            # 바다이면 체크안함
            if new_ice[x][y] == 0:
                continue

            # 얼음이면 개수 추가
            count_ice += 1

            # 현재 위치를 기준으로 주변 모든 얼음은 한덩어리 이므로
            # 주변을 탐색하며 같은 덩어리인 얼음은 0으로 만들어 줌
            visit = deque()
            visit.append((x, y,))
            while visit:
                vx, vy = visit.popleft()
                new_ice[vx][vy] = 0

                for dir in range(4):
                    nx = vx + dx[dir]
                    ny = vy + dy[dir]

                    # 범위 이내이며, 해당칸이 얼음일때(0이 아닐때)
                    # 0 처리후 방문가능위치 추가
                    if 0 <= nx < n and 0 <= ny < m and new_ice[nx][ny]:
                        # new_ice[nx][ny] = 0
                        visit.append((nx, ny,))

    return count_ice


###############################################
# 연산 시작
n, m = map(int, input().split())

ice_map = [list(map(int, input().split())) for _ in range(n)]

year = 0

while True:
    # 빙산의 개수를 세고
    count = Count_ice()

    # 두 덩어리로 나뉘어지면 년도 출력후 반복 종료
    if count >= 2:
        print(year)
        break

    # 한번에 0이 되면 0 출력후 반복 종료
    elif count == 0:
        print(0)
        break

    # 1년 후 얼음이 녹는다.
    year += 1
    ice_map = Melt_ice()

