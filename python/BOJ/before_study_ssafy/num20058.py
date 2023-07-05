import sys
input = sys.stdin.readline

########################################################
#값 입력 받기
n, q = map(int, input().split())

ice_graph = []

for _ in range(2**n):
    ice_graph.append(list(map(int, input().split())))

L = list(map(int, input().split()))

########################################################
#필요한 기본 정보
dx = [0,1,0,-1]
dy = [1,0,-1,0]

########################################################
#배열을 회전시키는 함수
def turn_cw(graph,l):
    new_graph = [[0 for _ in range(2**n)] for _ in range(2**n)]

    #i,j를 기준으로 2**l크기의 배열만 회전시킴
    for i in range(0, 2**n, 2**l):
        for j in range(0, 2 ** n, 2**l):
            for k in range(2**l):
                for m in range(2**l):
                    new_graph[i+k][j+m] = graph[i + (2**l - 1 - m)][j + k]

    return new_graph

########################################################
#줄어 들어야 하는 얼음을 체크
def melt_ice(graph):
    new_graph = [[0 for _ in range(2**n)] for _ in range(2**n)]

    #모든 얼음에 대해서
    for i in range(2**n):
        for j in range(2**n):

            ice_count = 0
            #4가지 방향을 체크
            for dir in range(4):
                nx = i + dx[dir]
                ny = j + dy[dir]

                #그 중에서 얼음이 있는 칸의 개수를 세기
                if 0 <= nx < 2**n and 0 <= ny < 2 ** n:
                    if graph[nx][ny] > 0:
                        ice_count += 1

            #얼음이 있는 칸이 3개 미만이면 -1 해서 넣고
            #아니면 그냥 바로 값을 넣어줌
            if ice_count < 3:
                new_graph[i][j] = graph[i][j] - 1
            else:
                new_graph[i][j] = graph[i][j]

    return new_graph

########################################################
#연산 수행
for i in range(q):
    ice_graph = turn_cw(ice_graph, L[i])
    ice_graph = melt_ice(ice_graph)

########################################################
#필요한 결과 계산
sum_ice = 0
check_ice = [[False for _ in range(2**n)] for _ in range(2**n)]
max_size = 0

for i in range(2 ** n):
    for j in range(2 ** n):
        #아직 체크하지 않은 칸인데 얼음이면
        if check_ice[i][j] == False and ice_graph[i][j] > 0:
            check = [[i, j]]
            sum_ice += ice_graph[i][j]
            check_ice[i][j] = True
            now_size = 1
            #그 칸을 기준으로 얼음 덩어리 찾기
            while check:
                x, y = check.pop(0)

                #4가지 방향에서
                for dir in range(4):
                    nx = x + dx[dir]
                    ny = y + dy[dir]

                    #범위 이내이고, 얼음이 있으며 방문하지 않은 칸일때
                    if 0 <= nx < 2**n and 0 <= ny < 2**n:
                        if ice_graph[nx][ny] > 0 and check_ice[nx][ny] == False:
                            #얼음의 크기를 세고 방문처리후 현재 얼음 덩어리 크기 + 1
                            sum_ice += ice_graph[nx][ny]
                            check.append([nx, ny])
                            check_ice[nx][ny] = True
                            now_size += 1

            max_size = max(max_size, now_size)



print(sum_ice)
print(max_size)