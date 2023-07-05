import sys
input = sys.stdin.readline
#############################################
n, x = map(int, input().split())

input_data = list(map(int, input().split()))


count = 0
for i in range(x):
    count += input_data[i]

answer = count
answer_count = 1

for i in range(x, n):
    count += input_data[i]
    count -= input_data[i-x]

    if answer < count:
        answer = count
        answer_count = 1

    elif answer == count:
        answer_count += 1
if answer == 0:
    print("SAD")

else:
    print(answer)
    print(answer_count)