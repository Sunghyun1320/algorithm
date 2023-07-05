import sys
input_ = sys.stdin.readline
#########################################
n, m = map(int, input_().split())

input_data = list(map(int, input_().split()))

sum_list = [0] * (n+1)

sum_temp = 0
for i in range(1, n+1):
    sum_temp += input_data[i-1]
    sum_list[i] += sum_temp

for _ in range(m):
    s, e = map(int, input_().split())

    print(sum_list[e] - sum_list[s-1])