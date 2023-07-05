import sys

input = sys.stdin.readline
###########################################
n = int(input())

circle = []

for circle_num in range(1, n + 1):
    x, r = map(int, input().split())

    circle.append([x - r, circle_num, 1])
    circle.append([x + r, circle_num, 0])

circle.sort()

stack = [[None, None, None]]

for point, num, check_ in circle:
    if point == stack[-1][0]:
        print("NO")
        break

    if check_ == 1:
        stack.append([point, num])
    else:
        if stack.pop(-1)[1] != num:
            print("NO")
            break

else:
    print("YES")