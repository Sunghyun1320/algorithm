import sys
input = sys.stdin.readline
#############################################
x, k = map(int, input().split())

i = 1
j = 1

answer = 0
while True:
    if j > k:
        break

    if i <= x and i & x:
        i = i << 1
        continue

    answer += i * int(bool((j & k)))
    j = j << 1
    i = i << 1

print(answer)
