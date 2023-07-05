import sys
input = sys.stdin.readline
#######################################################
INF = int(1e9)

n = int(input())
m = int(input())

# 경로 저장
path = [[[] for _ in range(n+1)] for _ in range(n+1)]

# 거리 저장
distance = [[INF for _ in range(n+1)] for _ in range(n+1)]

# 자기자신까지의 거리는 0
for i in range(n+1):
    distance[i][i] = 0

# 버스 정보 입력받기
for _ in range(m):
    a, b, c = map(int, input().split())

    # 같은 경로가 있을 수 있으므로, 거리가 작은 경우에만 갱신
    if distance[a][b] > c:
        distance[a][b] = c
        path[a][b] = [a, b]


# j에서 k로 갈때 기존 경로 vs i를 거쳐가는 경로를 비교
for i in range(1, n+1):
    for j in range(1, n+1):
        for k in range(1, n+1):
            if distance[j][k] > distance[j][i] + distance[i][k]:
                distance[j][k] = distance[j][i] + distance[i][k]
                path[j][k] = path[j][i] + path[i][k][1:]


# 결과 출력
for i in range(1, n+1):
    for j in range(1, n+1):
        if distance[i][j] == INF:
            print(0, end=" ")
        else:
            print(distance[i][j], end=" ")

        print()

for i in range(1, n+1):
    for j in range(1, n+1):
        print(len(path[i][j]), *path[i][j])

