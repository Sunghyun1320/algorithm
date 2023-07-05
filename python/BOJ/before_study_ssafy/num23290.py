import sys
from copy import deepcopy
input = sys.stdin.readline
##############################################################
#데이터 입력받기
m, s = map(int, input().split())


#4*4의 배열에 물고기 숫자, 남아있는 향기가 저장되어 있음
graph = [[[0]*9 for _ in range(4)] for _ in range(4)]
for _ in range(m):
    x, y, d = map(int, input().split())
    graph[x-1][y-1][d-1] += 1

shark_postion = list(map(int, input().split()))
shark_postion[0] -= 1
shark_postion[1] -= 1

##############################################################
#필요한 기본정보

dx = [0, -1, -1, -1, 0, 1, 1, 1]
dy = [-1, -1, 0, 1, 1, 1, 0, -1]

##############################################################
#물고기의 이동
def fish_move():
    new_graph = [[[0] * 9 for _ in range(4)] for _ in range(4)]

    for i in range(4):
        for j in range(4):
            for dir_index in range(9):
                if dir_index == 8:
                    new_graph[i][j][dir_index] = graph[i][j][dir_index]
                    continue

                if graph[i][j][dir_index] == 0:
                    continue

                dir = dir_index
                nx = i + dx[dir]
                ny = j + dy[dir]

                #격자 이내이고, 냄새가 없을때까지 반시계뱡향 회전
                #만약 갈수 있는 방향이 없다면 패스
                count = 1
                check_can_go = True

                while True:
                    #45도씩 돌리며 조건에 맞을때까지 반복
                    if 0 <= nx < 4 and 0 <= ny < 4 and graph[nx][ny][8] == 0 and [nx, ny] != shark_postion:
                        break

                    if count == 8:
                        check_can_go = False
                        break

                    dir = (dir - 1) % 8

                    nx = i + dx[dir]
                    ny = j + dy[dir]

                    count += 1

                #해당 물고기가 갈수있는 방향이 없으면 위치와 방향을 복원하고 다음 물고기 이동
                if check_can_go == False:
                    new_graph[i][j][dir_index] += graph[i][j][dir_index]
                    continue

                new_graph[nx][ny][dir] += graph[i][j][dir_index]

    return new_graph
##############################################################
#상어 움직임 찾기
def find_shark_move(depth, path, eat_fish, x, y):
    if depth == 3:
        global find_path, max_eat_fish
        #사전이 앞선 순으로 탐색하므로 같은 값일때 갱신 하지 않음
        if eat_fish > max_eat_fish:
            find_path = path
            max_eat_fish = eat_fish
        return

    #사전이 앞선 순으로 탐색
    for dir in range(2, -6, -2):
        dir = dir % 8

        path.append(dir)
        nx = x + dx[dir]
        ny = y + dy[dir]

        if 0 <= nx < 4 and 0 <= ny < 4:
            temp = []
            sum_fish = 0
            for dir_index in range(8):
                temp.append(new_graph[nx][ny][dir_index])
                sum_fish += new_graph[nx][ny][dir_index]
                new_graph[nx][ny][dir_index] = 0

            find_shark_move(depth+1, path[:], eat_fish + sum_fish, nx, ny)

            for dir_index in range(8):
                new_graph[nx][ny][dir_index] = temp[dir_index]

        path.pop(-1)


##############################################################
#상어가 움직임
def shark_move(path, shark_postion):

    for dir in path:
        nx = shark_postion[0] + dx[dir]
        ny = shark_postion[1] + dy[dir]

        for dir_index in range(8):
            if new_graph[nx][ny][dir_index] != 0:
                new_graph[nx][ny][dir_index] = 0
                new_graph[nx][ny][8] = 3

        shark_postion = [nx, ny]

    return shark_postion

##############################################################
#연산 수행
for _ in range(s):
    #물고기가 움직임
    new_graph = fish_move()

    #상어의 이동 찾기
    find_path = [2, 2, 2]
    max_eat_fish = -1
    find_shark_move(0, [], 0, shark_postion[0], shark_postion[1])

    #상어의 이동
    shark_postion = shark_move(find_path, shark_postion)

    #냄새 없어짐
    for i in range(4):
        for j in range(4):
            if new_graph[i][j][8] > 0:
                new_graph[i][j][8] -= 1

    #복제된 물고기 추가 후 갱신
    for i in range(4):
        for j in range(4):
            for dir_index in range(8):
                new_graph[i][j][dir_index] += graph[i][j][dir_index]

    graph = deepcopy(new_graph)

##############################################################
#원하는 값 찾기
answer = 0
for i in range(4):
    for j in range(4):
        for dir_index in range(8):
            answer += graph[i][j][dir_index]

print(answer)
















