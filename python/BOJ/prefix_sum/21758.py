import sys
input = sys.stdin.readline
########################################
n = int(input())

data = list(map(int, input().split()))

sum_data = [0 for _ in range(n+1)]

sum_sweet = 0

for i in range(1, n+1):
    sum_sweet += data[i-1]
    sum_data[i] = sum_sweet

# 벌 집 벌 의 형태인 경우
# 양 끝을 제외한 칸중에 가장 큰 값
max_sweet = max(data[1:-1])
answer = sum_sweet - data[0] - data[-1] + max_sweet

# 벌 벌 집 의 경우
# 집 벌 벌 의 경우
for i in range(2, n):
    bee_bee_house = sum_sweet - data[0] - data[i-1] + sum_sweet - sum_data[i]
    house_bee_bee = sum_sweet - data[-1] - data[i-1] + sum_data[i-1]
    answer = answer if answer > bee_bee_house else bee_bee_house
    answer = answer if answer > house_bee_bee else house_bee_bee

print(answer)