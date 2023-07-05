import sys
input = sys.stdin.readline
###########################################
n, k = map(int, input().split())
input_data = list(map(int, input().split()))

# 누적 합 딕셔너리
sum_list = [0 for _ in range(1000)]
sum_list[0] = 1

# for i in range(0, 1001, k):
#     sum_dict[i] = 1


sum_ = 0
answer = 0

for i in input_data:
    sum_ += i

    answer += sum_list[sum_ % k]

    # 누적 합 딕셔너리 갱신
    sum_list[sum_ % k] += 1

print(answer)
