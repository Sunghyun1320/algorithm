from collections import deque
import sys
input = sys.stdin.readline
##########################################
t = int(input())

for _ in range(t):
    left_deque = deque()
    right_deque = deque()

    password_data = input().rstrip()

    for char in password_data:
        if char == "<":
            if left_deque:
                right_deque.appendleft(left_deque.pop())
            else:
                continue

        elif char == ">":
            if right_deque:
                left_deque.append(right_deque.popleft())
            else:
                continue

        elif char == "-":
            if left_deque:
                left_deque.pop()
            else:
                continue

        else:
            left_deque.append(char)

    print("".join(left_deque) + "".join(right_deque))



