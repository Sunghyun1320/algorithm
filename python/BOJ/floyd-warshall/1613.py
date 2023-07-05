import sys
input = sys.stdin.readline
############################################
n, k = map(int, input().split())

# 각 최단경로를 저장할 2차원 배열
distance = [[0] * (n+1) for _ in range(n+1)]

# a 다음 b가 발생했다면 a -> b 경로로 설정
for _ in range(k):
    a, b = map(int, input().split())
    distance[a][b] = 1

# 플로이드 워셜 j > k의 경로가 있다면 j 다음에 k 사건 발생했음
for i in range(1, n+1):
    for j in range(1, n+1):
        for k in range(1, n+1):
            if distance[j][i] == 1 and distance[i][k] == 1:
                distance[j][k] = 1

t = int(input())


for _ in range(t):
    # 두 사건에 대해서
    a, b = map(int, input().split())


    # a -> b 경로가 있다면 a가 먼저 발생
    if distance[a][b] == 1:
        print(-1)

    # 그게 아니면 b -> a 경로가 있으므로 b가 먼저 발생
    elif distance[b][a] == 1:
        print(1)

    # 서로간의 경로가 모두 없다면 판정 불가
    else:
        print(0)
