import sys
input = sys.stdin.readline
#################################################
n = int(input())

sequence = []
for _ in range(n):
    sequence.append(int(input()))

stack = [-1]
i = 1

answer = []

while sequence:
    if stack[-1] == sequence[0]:
        stack.pop(-1)
        sequence.pop(0)
        answer.append("-")

    elif stack[-1] != sequence[0]:
        stack.append(i)
        i += 1
        answer.append("+")

    if sequence and stack[-1] > sequence[0]:
        print("NO")
        exit()

for char in answer:
    print(char)