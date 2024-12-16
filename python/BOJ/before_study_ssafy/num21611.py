import sys
input = sys.stdin.readline
########################################################
#필요한 기본 정보
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

#문제에서 제시된 2차원 배열의 번호를 만드는 함수
def make_graph():
    #번호를 저장해서 반환할 배열
    graph = [[0] * n for _ in range(n)]

    #시작위치
    x, y = 0, -1

    #함수 내에서 사용할 방향
    dx = [0, 1, 0, -1]
    dy = [1, 0, -1, 0]
    dir = 0

    for i in range(n ** 2 - 1, 0, -1):
        nx = x + dx[dir]
        ny = y + dy[dir]

        #벽을 만나거나 값이 채워진 위치에서 방향 전환
        if nx < 0 or nx >= n or ny < 0 or ny >= n or graph[nx][ny] != 0:
            dir = (dir + 1) % 4

            nx = x + dx[dir]
            ny = y + dy[dir]

        graph[nx][ny] = i
        x, y = nx, ny

    return graph

########################################################
#데이터 입력받기
n, m = map(int, input().split())

#문제에서 주어진 상어를 중심으로 1씩 증가하는 2차원 행렬
graph = make_graph()

#2차원에 있는 구슬들을 모두 1차원 배열형태로 저장
boll = [0] * (n**2)

for i in range(n):
    a = list(map(int, input().split()))
    for j in range(n):
        boll[graph[i][j]] = a[j]


order = []
for _ in range(m):
    order.append(list(map(int, input().split())))

########################################################
#부숴지는 구슬의 위치를 받아서
#빈칸을 모두 채운뒤의 구슬들을 반환하는 함수
def crash_boll(crash_list):
    new_boll = []

    for i in range(len(boll)):
        # 부숴지는위치의 index면 다음 반복
        if i in crash_list:
            continue
        new_boll.append(boll[i])

        #구슬들을 모두 채웠을때 종료
        if i != 0 and boll[i] == 0:
            break

    return new_boll

########################################################
#4개 이상 이어진 공이 있으면 폭발하고
#폭발여부와 폭발후 빈칸을 채운 구슬들을 반환
def boom_boll():
    global boom_count

    count = 0
    now_num = boll[1]

    #만약에 폭발하지 않았으면 False를 반환하여
    #폭발을 더 할지 말지 판단하기 위한 bool
    bool_boom = False

    #공들을 하나씩 살펴볼때
    for i in range(1, len(boll)):
        #같은 공연결이면 개수 추가
        if now_num == boll[i]:
            count += 1

        #다른 공이 나왔을때
        else:
            #폭발해야 한다면
            if count >= 4:
                #폭발한 번호와 개수를 index,value로 저장
                boom_count[now_num] += count
                #폭발이 일어났으므로 폭발여부 한번더 봐야됨
                bool_boom = True
                #폭발이 일어난 구슬은 0으로 바꿔줌
                for j in range(i-1, i-count-1, -1):
                    boll[j] = 0

                count = 1
                now_num = boll[i]
            else:
                count = 1
                now_num = boll[i]

    #0번위치는 상어의 위치
    new_boll = [0]

    for i in range(len(boll)):
        if boll[i] != 0:
            new_boll.append(boll[i])
    new_boll.append(0)

    return bool_boom, new_boll

########################################################
#구슬의 분리
def separate_boll():

    new_boll = [0]
    count = 0
    now_num = boll[1]

    #모든 구슬들을 보며
    for i in range(1, len(boll)):
        #같은 그룹이면 카운트 세기
        if boll[i] == now_num:
            count += 1
        #아니면 카운트와 번호를 추가하되
        #추가한뒤 공들의 개수가 영역보다 많으면 그만
        else:
            new_boll.append(count)
            if len(new_boll) == (n**2):
                break

            new_boll.append(now_num)
            if len(new_boll) == (n**2):
                break

            count = 1
            now_num = boll[i]

    new_boll.append(0)
    return new_boll

########################################################
#연산 수행
#1,2,3에 폭발한 공의 개수가 저장되어 있음
boom_count = [0]*4

for dir, range_ in order:
    #dir이 1,2,3,4로 구분되기 때문에 -1
    dir -= 1

    #공격한 공의 index찾기
    crash = []
    for i in range(1, range_+1):
        crash_x = n//2 + (i * dx[dir])
        crash_y = n//2 + (i * dy[dir])

        crash.append(graph[crash_x][crash_y])

    #공을 부숴줌
    boll = crash_boll(crash)

    #폭발했는지 체크하며 폭발시키기
    #폭발 안했으면 스톱
    check_boll = True
    while True:
        if check_boll == False or len(boll) == 1:
            break
        check_boll, boll = boom_boll()

    if len(boll) == 1:
        break
    #공 분리 시키기
    boll = separate_boll()

########################################################
#원하는 값 출력

answer = 0

for i in range(1, 4):
    answer += i * boom_count[i]

print(answer)



