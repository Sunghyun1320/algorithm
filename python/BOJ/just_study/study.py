import sys
input = sys.stdin.readline
#############################################
n = int(input())
soldier = list(map(int, input().split()))

data = [1] * n

for i in range(n):
    for j in range(i):
        if soldier[i] < soldier[j]:
            data[i] = max(data[j] + 1, data[i])
            print(data)

print(n - max(data))