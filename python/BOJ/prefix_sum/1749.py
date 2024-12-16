import sys
input = sys.stdin.readline
################################################
n, m = map(int, input().split())

data = []

for i in range(n):
    data.append(list(map(int, input().split())))


sum_data = [[0 for _ in range(m+1)] for _ in range(n+1)]

# 누적 합 구하기
for i in range(1, n+1):
    for j in range(1, m+1):
        sum_data[i][j] = sum_data[i][j-1] + data[i-1][j-1] + sum_data[i-1][j] - sum_data[i-1][j-1]


answer = int(-10e9)

for x1 in range(1, n+1):
    for y1 in range(1, m+1):
        for x2 in range(x1, n+1):
            for y2 in range(y1, m+1):
                answer = max(answer, sum_data[x2][y2] - sum_data[x1-1][y2] - sum_data[x2][y1-1] + sum_data[x1 - 1][y1 - 1])

print(answer)

