import sys
sys.stdin = open("input.txt")
#############################################
# 문제 해결에 필요한 정보들
# 우 하 좌 상
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

# 블록과 충돌 후 진입방향에 따른 진출 방향
# ex 1번 블록에 왼쪽방향(2)으로 진입시 위쪽(3)으로 진출
change_dir = [[], [2, 0, 3, 1], [2, 3, 1, 0], [1, 3, 0, 2], [3, 2, 0, 1], [2, 3, 0, 1]]
#############################################
# 그래프의 좌표와 시작 방향을 입력받아 점수를 구하는 함수
def check_point(x, y, dir):
    nx = x
    ny = y

    point = 0
    while True:
        nx += dx[dir]
        ny += dy[dir]

        if nx < 0 or nx >= n or ny < 0 or ny >= n or graph[nx][ny] == 5:
            point = point * 2 + 1
            break

        # 블랙홀을 만났을 경우 현재 점수 그대로 가지고 리턴
        if graph[nx][ny] == -1 or (nx == x and ny == y):
            break

        # 웜홀을 만났을 경우
        if graph[nx][ny] >= 6 and graph[nx][ny] <= 10:
            nx, ny = hole[(nx, ny)]

        # 각진 블록을 만났을 경우
        elif graph[nx][ny] >= 1 and graph[nx][ny] <= 4:
            new_dir = change_dir[graph[nx][ny]][dir]
            if new_dir == (dir + 2) % 4:
                point = point * 2 + 1
                break
            point += 1
            dir = change_dir[graph[nx][ny]][dir]

        else:
            check_graph[nx][ny][dir] = True


    global answer
    if point > answer:
        answer = point


#############################################
T = int(input())

for test_case in range(1, T+1):
    # 데이터 입력 받기
    ##########################################################
    n = int(input())

    temp = {}
    hole = {}
    graph = []

    for i in range(n):
        a = list(map(int, input().split()))
        for j in range(n):
            if a[j] >= 6 and a[j] <= 10:
                if temp.get(a[j], False):
                    hole[temp[a[j]]] = (i, j)
                    hole[(i, j)] = temp[a[j]]
                else:
                    temp[a[j]] = (i, j)

        graph.append(a)

    ##########################################################

    check_graph = [[[False for _ in range(4)] for _ in range(n)] for _ in range(n)]
    answer = 0
    for i in range(n):
        for j in range(n):
            # 해당 칸이 빈칸이 아니면 패스
            if graph[i][j] != 0:
                continue

            for dir in range(4):
                if check_graph[i][j][dir]:
                    continue

                check_graph[i][j][dir] = True
                check_point(i, j, dir)

    print(f"#{test_case} {answer}")



