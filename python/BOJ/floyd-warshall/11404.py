INF = int(10e9)

n = int(input())
m = int(input())

result = [[INF] * (n + 1) for _ in range(n + 1)]

for i in range(n + 1):
    result[i][i] = 0

for _ in range(m):
    a, b, c = map(int, input().split())
    if result[a][b] > c:
        result[a][b] = c

for i in range(1, n + 1):
    for j in range(1, n + 1):
        for k in range(1, n + 1):
            result[j][k] = min(result[j][k], result[j][i] + result[i][k])

for i in range(1, n + 1):
    for j in range(1, n + 1):
        if result[i][j] == INF:
            print(0, end=" ")
        else:
            print(result[i][j], end=" ")
    print()


