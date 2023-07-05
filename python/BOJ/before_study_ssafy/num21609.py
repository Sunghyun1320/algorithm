import sys
input = sys.stdin.readline
##########################################################
#데이터 입력받기
n, m = map(int, input().split())

game_map = []
for _ in range(n):
    game_map.append(list(map(int, input().split())))

##########################################################
#격자 반시계 방향 회전
def turn_ccw(graph):
    new_graph = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        for j in range(n):
            new_graph[i][j] = graph[j][n-1-i]

    return new_graph

##########################################################
#중력의 작용
def gravity(graph):

    for j in range(n):
        for i in range(n-1, -1, -1):
            if graph[i][j] >= 0:
                for k in range(i+1, n+1):
                    if k == n or graph[k][j] >= -1:
                        graph[i][j], graph[k-1][j] = graph[k-1][j], graph[i][j]
                        break

##########################################################
dx = [0,1,0,-1]
dy = [1,0,-1,0]

#최대 크기 블록 찾기
def find_max_block(graph):
    max_block = [[0, 0]]
    max_count = 0
    max_rainbow_count = 0
    visited = [[False for _ in range(n)] for _ in range(n)]

    #큰행, 큰열이 우선순위이므로 우선순위 블록 먼저 탐색함
    for i in range(n):
        for j in range(n):
            #지금 칸이 일반 블록이 아니거나 이미 처리한 블록이면 패스
            if graph[i][j] <= 0 or visited[i][j]:
                continue

            #방문처리후 숫자 저장
            visited[i][j] = True
            now_num = graph[i][j]

            #블록그룹 만들기
            block = [[i, j]]
            count = 0
            rainbow_count = 0

            for x, y in block:
                for dir in range(4):
                    nx = x + dx[dir]
                    ny = y + dy[dir]

                    if not(0 <= nx < n and 0 <= ny < n):
                        continue

                    #기준블록과 같은 블록그룹이면 방문처리, 블록그룹 묶기
                    if graph[nx][ny] == now_num and visited[nx][ny] == False:
                        block.append([nx, ny])
                        visited[nx][ny] = True
                        count += 1

                    #무지개 블록인경우 지금 블록 그룹에 없으면 추가
                    elif graph[nx][ny] == 0 and [nx,ny] not in block:
                        block.append([nx, ny])
                        visited[nx][ny] = True
                        count += 1
                        rainbow_count += 1

            #최대 블록 크기일시 갱신
            if count > max_count:
                max_block = block
                max_count = count
                max_rainbow_count = rainbow_count

            #같은 크기일시 무지개 블록 개수로 갱신
            #크기가 같고 무지개 블록이 같은경우 나중에 탐색된 블록 그룹이 우선이므로 갱신
            elif count == max_count:
                if rainbow_count >= max_rainbow_count:
                    max_block = block
                    max_count = count
                    max_rainbow_count = rainbow_count



    #블록 그룹이 없는 경우 None 반환
    if len(max_block) == 1:
        return None

    return max_block
##########################################################

reward = 0
while True:
    remove_block = find_max_block(game_map)

    if remove_block == None:
        break

    reward += len(remove_block) ** 2

    for x, y in remove_block:
        game_map[x][y] = -2

    gravity(game_map)
    game_map = turn_ccw(game_map)
    gravity(game_map)

print(reward)
