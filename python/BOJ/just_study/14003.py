import sys
input = sys.stdin.readline
###############################################
def lower(arr, num):
    left, right = 0, len(arr)

    while left < right:
        mid = left + (right - left) // 2

        if arr[mid] < num:
            left = mid + 1

        else:
            right = mid

    return right


###############################################
t = int(input())

arr = list(map(int, input().split()))

dp = [-1000000001]
answer = [(-1000000001, 0)]

for i in range(t):
    if dp[-1] < arr[i]:
        answer.append((arr[i], len(dp)))
        dp.append(arr[i])

    else:
        index = lower(dp, arr[i])
        dp[index] = arr[i]
        answer.append((arr[i], index))

size = len(dp) - 1
print(size)

new_ans = []
for i in range(len(answer) - 1, 0, -1):
    if answer[i][1] == size:
        new_ans.append(answer[i][0])
        size -= 1

print(*new_ans[::-1])



