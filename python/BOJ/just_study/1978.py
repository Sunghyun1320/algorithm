n = int(input())

count = 0
num = [False for _ in range(1001)]
num[1] = True

for i in range(2, 1001):
    if num[i]:
        continue
    for j in range(i*2, 1001, i):
        num[j] = True

for i in map(int, input().split()):
    if not num[i]:
        count += 1

print(count)
