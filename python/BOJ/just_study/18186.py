import sys
input = sys.stdin.readline
####################################################
# n = int(input())
# b = 3
# c = 2

n, b, c = map(int, input().split())

count_buy = list(map(int, input().split()))
lamen = [[0, 0], [0, 0]]
answer = 0

if b > c:
    for i in range(n - 1):
        answer += count_buy[i] * b
        answer += lamen[0][0] * c
        answer += lamen[0][1] * c

        # 이번 단계에서 3원에 사는 라면이 있으면
        # 다음단계에서 2원에 살수있는 라면만큼 추가함
        if count_buy[i+1] > count_buy[i]:
            lamen[1][0] += count_buy[i]
            count_buy[i+1] -= count_buy[i]

        else:
            lamen[1][0] += count_buy[i+1]
            count_buy[i+1] = 0

        # 이번 단계에서 2원에 살수 있는 라면이 있으면
        # 다음단계에서 2원에 살 수 있는 라면만큼 추가함
        if count_buy[i+1] > lamen[0][0]:
            lamen[1][1] += lamen[0][0]
            count_buy[i+1] -= lamen[0][0]

        else:
            lamen[1][1] += count_buy[i+1]
            count_buy[i+1] = 0

        lamen[0][0] = lamen[1][0]
        lamen[0][1] = lamen[1][1]
        lamen[1] = [0, 0]

    answer += count_buy[n-1] * b
    answer += lamen[0][0] * c
    answer += lamen[0][1] * c

    print(answer)

else:
    for i in range(n - 1):
        answer += count_buy[i] * b

    print(answer)

