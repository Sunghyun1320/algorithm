import sys
input = sys.stdin.readline
############################################################
#데이터 입력받기
n, m = map(int, input().split())

graph = []
for _ in range(n):
    graph.append(list(map(int, input().split())))

order = []
for _ in range(m):
    order.append(list(map(int, input().split())))

############################################################
#필요한 기본정보
dx = [0, -1, -1, -1, 0, 1, 1, 1]
dy = [-1, -1, 0, 1, 1, 1, 0, -1]

cloud = [[n-1, 0], [n-1, 1], [n-2, 0], [n-2, 1]]

############################################################
#모든 명령에 대해서
for dir, speed in order:
    #모든 구름들이
    for i in range(len(cloud)):
        #위치를 옮김
        x = cloud[i][0] + (speed * dx[dir - 1])
        y = cloud[i][1] + (speed * dy[dir - 1])

        #영역을 벗어났을때 다시 이어지므로 나머지 처리
        x %= n
        y %= n

        #비가와서 물이 추가
        graph[x][y] += 1

        cloud[i] = [x, y]

    for x, y in cloud:

        #대각선 방향으로 물복사 버그
        for dir_ in range(1, 8, 2):
            nx = x + dx[dir_]
            ny = y + dy[dir_]

            if 0 <= nx < n and 0 <= ny < n:
                #구름이 사라진 칸인지 체크하기위해 음수처리를 하므로
                #음수인 경우에도 물이 있는 경우임
                if graph[nx][ny] != 0:
                    graph[x][y] += 1

        #구름을 생성할때 구름이 사라진 칸인지 체크하기 위한 음수처리
        graph[x][y] *= -1

    #구름이 모두 사라진다.
    cloud.clear()

    #모든 바구니를 돌며 구름 생성
    #이때 구름이 사라졌던 칸은 음수이므로 구름이 생성되지 않고
    #음수인칸은 다시 양수로 바꿔줌
    for i in range(n):
        for j in range(n):
            if graph[i][j] >= 2:
                cloud.append([i, j])
                graph[i][j] -= 2

            elif graph[i][j] < 0:
                graph[i][j] *= -1

############################################################
#원하는 값 찾기
answer = 0

for i in range(n):
    for j in range(n):
        answer += graph[i][j]

print(answer)