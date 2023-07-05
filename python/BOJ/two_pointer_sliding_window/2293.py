import sys
input = sys.stdin.readline
##########################################
n, k = map(int, input().split())

# 이전단계의 경우의수를 저장하는 리스트
dp = [0 for _ in range(k+1)]

for i in range(n):
    # 이번 코인가치에 따른 경우의 수를 저장하는 리스트
    new_arr = [0 for _ in range(k+1)]
    coin_cost = int(input())
    # 만약 코인의 가치가 k보다 크면 고려할 필요 없음
    if coin_cost > k:
        continue

    # 코인 가치보다 작은 수는 이전까지 경우의수 그대로 가져감
    for j in range(coin_cost):
        new_arr[j] = dp[j]

    # 0가치는 모두 0개 넣으면 되니까 1로 통일됨
    new_arr[0] = 1

    # 경우의 수는 이번 코인을 사용하지 않는 경우의수(dp[j]) 와
    # 이번 코인을 포함해서 k-cost의 경우의 수(new_arr[j-coin_cost] 의 합
    # 두번째 경우의 수는 k-cost에서 cost동전 하나만 추가된 케이스
    for j in range(coin_cost, k+1):
        new_arr[j] = dp[j] + new_arr[j-coin_cost]

    dp = new_arr.copy()


print(new_arr[k])