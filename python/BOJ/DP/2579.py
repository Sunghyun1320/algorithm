# 1
# 12
# 13 23
# 124 134
# 135 235 1245
# 1246 1346 1356 2356

import sys
input = sys.stdin.readline
#############################################
n = int(input())
if n == 1:
    print(int(input()))
    exit()

step = [int(input()) for _ in range(n)]

answer = [0] * n
answer[0] = step[0]
answer[1] = step[0] + step[1]

for i in range(2, n):
    answer[i] = max(answer[i-2] + step[i], answer[i-3] + step[i-1] + step[i])

print(answer[n-1])
