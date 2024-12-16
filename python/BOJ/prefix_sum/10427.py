import sys
input = sys.stdin.readline
##############################################
def Sort(list_):
    for i in range(len(list_)):
        for j in range(len(list_) - i - 1):
            if list_[j] > list_[j+1]:
                list_[j], list_[j+1] = list_[j+1], list_[j]
##############################################

t = int(input())

for _ in range(t):
    n, *money = map(int, input().split())

    # 각 비용의 차이를 최소화 하기 위한 정렬
    Sort(money)

    answer = 0

    # S(1) ~ S(N)까지 구하기 위한 반복
    # S(1) ==  0 이므로 2부터 반복
    for i in range(2, n+1):
        sum_ = 0
        # 첫 0~i 까지 구간합
        for j in range(i):
            sum_ += money[j]
        min_value = money[i-1]*i - sum_

        # j~j+i 까지 구간합을 구해서 빚의 차이 계산후 최소값 갱신
        for j in range(i, n):
            sum_ = sum_ + money[j] - money[j-i]
            min_value = min_value if min_value < (money[j] * i) - sum_ else (money[j] * i) - sum_

        # S(i)의 최소값 더하기
        answer += min_value

    print(answer)