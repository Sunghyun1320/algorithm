import sys
input = sys.stdin.readline
####################################################
r, c, k = map(int, input().split())

heater_postion = []
check_point = []

for i in range(r):
    a =  list(map(int, input().split()))
    for j in range(c):
        #위치와 방향정보를 저장
        #단 방향은 내가 정한 dx,dy기준으로 바꿈
        if a[j] == 1:
            heater_postion.append([i, j, 1])

        elif a[j] == 2:
            heater_postion.append([i, j, 3])

        elif a[j] == 3:
            heater_postion.append([i, j, 2])

        elif a[j] == 4:
            heater_postion.append([i, j, 0])

        elif a[j] == 5:
            check_point.append([i, j])

room_graph = [[0]*c for _ in range(r)]

w = int(input())
wall = [[[True,True,True,True] for _ in range(c)] for _ in range(r)]
for _ in range(w):
    x, y, t = map(int,input().split())
    if  t == 0:
        wall[x-1][y-1][2] = False
        wall[x-2][y-1][0] = False
    elif t == 1:
        wall[x-1][y-1][1] = False
        wall[x-1][y][3] = False


####################################################
#필요한 기본정보
dx = [1,0,-1,0]
dy = [0,1,0,-1]

####################################################
#온풍기에서 바람이 나옴
def turn_on_heater(room_graph):
    for x, y, dir in heater_postion:
        new_room = [[0] * c for _ in range(r)]

        nx = x + dx[dir]
        ny = y + dy[dir]

        heat_point = [[nx, ny]]
        new_room[nx][ny] = 5
        room_graph[nx][ny] += 5

        for nx, ny in heat_point:
            temp = new_room[nx][ny] - 1
            if temp == 0:
                break

            #dir방향 먼저 온도 올림
            #벽이 없으면
            if wall[nx][ny][dir]:
                nnx = nx + dx[dir]
                nny = ny + dy[dir]

                if 0 <= nnx < r and 0 <= nny < c:
                    #이번 히터로 데워진 칸이 아닐때
                    if new_room[nnx][nny] == 0:
                        new_room[nnx][nny] = temp
                        room_graph[nnx][nny] += temp
                        heat_point.append([nnx,nny])

            #수직으로 한칸씩 한 칸의 온도 변화
            for i in range(-1,2,2):
                if wall[nx][ny][(dir + i) % 4]:
                    nnx = nx + dx[(dir + i) % 4]
                    nny = ny + dy[(dir + i) % 4]
                    if 0 <= nnx < r and 0 <= nny < c:
                       if wall[nnx][nny][dir]:
                            nnx = nnx + dx[dir]
                            nny = nny + dy[dir]
                            if 0 <= nnx < r and 0 <= nny < c:
                                if new_room[nnx][nny] == 0:
                                    new_room[nnx][nny] = temp
                                    room_graph[nnx][nny] += temp
                                    heat_point.append([nnx, nny])

####################################################
#온도조절
def control_temperature():
    new_room = [[0]*c for _ in range(r)]

    for i in range(r):
        for j in range(c):
            temp = room_graph[i][j]
            for dir in range(4):
                nx = i + dx[dir]
                ny = j + dy[dir]

                #비교하는 칸이 범위 이내이고 해당 칸으로 벽이 없을때
                if 0 <= nx < r and 0 <= ny < c and wall[i][j][dir]:
                    if room_graph[i][j] > room_graph[nx][ny]:
                        temp -= (room_graph[i][j] - room_graph[nx][ny]) // 4
                        new_room[nx][ny] += (room_graph[i][j] - room_graph[nx][ny]) // 4

            new_room[i][j] += temp

    return new_room

####################################################
#바깥쪽 온도 하락
def temperature_down():
    for i in range(c):
        if room_graph[0][i] > 0:
            room_graph[0][i] -= 1
        if room_graph[-1][i] > 0:
            room_graph[-1][i] -= 1

    for i in range(1,r-1):
        if room_graph[i][0] > 0:
            room_graph[i][0] -= 1
        if room_graph[i][-1] > 0:
            room_graph[i][-1] -= 1

####################################################
#체크 포인트 체크
def check_end():
    #모든 체크포인트에서
    for x, y in check_point:
        #k보다 미만인 온도가 있으면 아직 안끝났다고 리턴
        if room_graph[x][y] < k:
            return False
    #체크포인트 다 돌았는데도 미만인 온도가 없으면
    #끝!!
    return True

####################################################
#연산 수행
count = 0

while True:
    if count > 100:
        print(101)
        break

    turn_on_heater(room_graph)
    room_graph = control_temperature()
    temperature_down()
    count += 1
    if check_end():
        print(count)
        break
