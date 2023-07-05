import sys
input = sys.stdin.readline
from collections import deque
##################################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
##################################################
r, c = map(int, input().split())

# 호수의 상태
lack = [list(input().rstrip()) for _ in range(r)]
# 물을 기준으로 녹일 얼음을 찾는 bfs용 큐
water = deque()
# 백조를 기준으로 다른 백조를 찾을때 사용할 bfs용 큐
swan = deque()
# bfs를 중간에 끊기위해 다음 노드를 임시로 저장할 큐
temp = deque()
# 백조가 탐색을 할때 방문 처리를 해줄 노드
visited = [[False for _ in range(c)] for _ in range(r)]
##################################################
# 얼음을 녹이고, 녹은 얼음을 임시큐에 저장하는 함수
def melt_ice():
    while water:
        x, y = water.popleft()

        for dir in range(4):
            nx = x + dx[dir]
            ny = y + dy[dir]

            if nx < 0 or nx >= r or ny < 0 or ny >= c or lack[nx][ny] != "X":
                continue

            # 물과 닿은 얼음을 녹이고
            # 물과 닿은 얼음만 녹이기 위해 임시큐에 저장
            lack[nx][ny] = "."
            temp.append([nx, ny])

##################################################
# 얼음으로 가지 못하는 영역을 임시 큐에 저장하고, 백조를 만났는지 여부를 반환하는 함수
def check_meet():
    while swan:
        x, y = swan.popleft()

        for dir in range(4):
            nx = x + dx[dir]
            ny = y + dy[dir]

            if nx < 0 or nx >= r or ny < 0 or ny >= c or visited[nx][ny]:
                continue

            visited[nx][ny] = True

            # 물과 맞닿은 얼음이면 임시 큐에 저장
            if lack[nx][ny] == "X":
                temp.append([nx, ny])

            # 물이면 계속 탐색해야하므로 백조의 경로에 저장
            elif lack[nx][ny] == ".":
                swan.append([nx, ny])

            # 백조를 만났으면 True반환
            elif lack[nx][ny] == "L":
                return True

    # 백조를 못만나고 현재거리의 노드 모두 돌았으면 False반환
    return False


##################################################
# 물과 백조의 위치를 저장
for i in range(r):
    for j in range(c):
        # 얼음이 아니면 물에 추가
        # 백조의 위치도 물임
        if lack[i][j] != "X":
            water.append([i, j])

        # 백조의 시작점 한마리만 저장하고 해당위치 방문처리
        if not swan and lack[i][j] == "L":
            swan.append([i, j])
            visited[i][j] = True

##################################################
# 0일부터 시작
day = 0
while True:
    # 이번 날에 만났으면 날짜 출력 후 멈춤
    if check_meet():
        print(day)
        break
    # 못만났으면 임시큐 가져온 다음
    swan = temp
    temp = deque()
    # 얼음 녹이기
    melt_ice()
    # 임시 큐 저장,
    water = temp
    temp = deque()
    # 다음날 체크
    day += 1





