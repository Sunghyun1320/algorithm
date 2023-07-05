import sys
input = sys.stdin.readline
###############################################################
#데이터 입력받기
n, m, k = map(int, input().split())

map_graph = []

for _ in range(n):
    map_graph.append(list(map(int, input().split())))

###############################################################
#필요한 기본정보
#0이 동쪽 +1일때 시계방향 90도 -1일때 반시계방향 90도
dx = [0,1,0,-1]
dy = [1,0,-1,0]

#초기방향은 동쪽
dir = 0

#초기 주사위 세팅
dice_postion = [0,0]
bottom = 6
tap = 1
east = 3
west = 4
north = 2
south = 5

###############################################################
#각 칸에서 획득할 수 있는 점수를 미리 계산해둔다.
visited = [[False]*m for _ in range(n)]

map_reward = [[0]*m for _ in range(n)]

for i in range(n):
    for j in range(m):
        if visited[i][j]:
            continue

        visited[i][j] = True

        this_box = [[i,j]]
        this_num = map_graph[i][j]
        count = 1
        for x, y in this_box:
            for dir_ in range(4):
                nx = x + dx[dir_]
                ny = y + dy[dir_]

                if 0 <= nx < n and 0 <= ny < m and visited[nx][ny] == False:
                    if map_graph[nx][ny] == this_num:
                        this_box.append([nx, ny])
                        visited[nx][ny] = True
                        count += 1

        for x, y in this_box:
            map_reward[x][y] = this_num * count

###############################################################
#주사위 구르기
def Dice_roll(bottom, tap, east, west, north, south, dir):
    #동쪽으로 구른경우
    if dir == 0:
        bottom, tap, east, west = east, west, tap, bottom

    #서쪽으로 구른경우
    elif dir == 2:
        bottom, tap, east, west = west, east, bottom, tap

    #남쪽으로 구른경우
    elif dir == 1:
        bottom, tap, north, south = south, north, bottom, tap

    #북쪽으로 구른경우
    elif dir == 3:
        bottom, tap, north, south = north, south, tap, bottom

    return bottom, tap, east, west, north, south

###############################################################
#연산 수행

for i in map_reward:
    print(i)
# answer = 0
# for _ in range(k):
#     x, y = dice_postion
#
#     nx = x + dx[dir]
#     ny = y + dy[dir]
#
#     #범위 이탈 체크
#     if 0 <= nx < n and 0 <= ny < m:
#         pass
#     #범위 이탈시 방향 반대로
#     else:
#         dir = (dir + 2) % 4
#         nx = x + dx[dir]
#         ny = y + dy[dir]
#
#     #점수 추가
#     answer += map_reward[nx][ny]
#
#     #주사위 구르기
#     bottom, tap, east, west, north, south = Dice_roll(bottom, tap, east, west, north, south, dir)
#     dice_postion = [nx, ny]
#
#     #방향 갱신
#     #A > B인 경우 시계방향으로 90도 회전
#     if bottom > map_graph[nx][ny] :
#         dir = (dir + 1) % 4
#
#     #A < B인 경우 반시계 방향으로 90도 회전
#     elif bottom < map_graph[nx][ny] :
#         dir = (dir - 1) % 4
#
#     #같을 경우 아무것도 안함
#     else:
#         pass
#
#
# print(answer)