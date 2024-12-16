import sys
input = sys.stdin.readline
###########################################
t = int(input())

for _ in range(t):
    input_data = list(input())

    check_ = 0

    for char in input_data:
        if char == "(":
            check_ += 1
        elif char == ")":
            check_ -= 1

        if check_ < 0:
            break

    if check_ == 0:
        print("YES")
    else:
        print("NO")