import sys
input = sys.stdin.readline
###############################################
def lower(arr, num):
    left, right = 0, len(arr)

    while left < right:
        mid = left + (right - left)//2

        if arr[mid] <= num:
            left = mid + 1

        else:
            right = mid

    return right


###############################################
n, m = map(int, input().split())

t = int(input())

cat = []

for _ in range(t):
    cx, cy = map(int, input().split())
    if cx < 0 or cx > n or cy < 0 or cy > m:
        continue

    cat.append([cx, cy])

if len(cat) == 0:
    print(0)
    exit()

cat.sort()
dp = [-1]
check_2 = [(-1, 0)]

for i in range(len(cat)):
    if dp[-1] <= cat[i][1]:
        check_2.append((i, len(dp)))
        dp.append(cat[i][1])

    else:
        index = lower(dp, cat[i][1])
        dp[index] = cat[i][1]
        check_2.append((i, index))

# size = len(dp) - 1
print(len(dp) - 1)
