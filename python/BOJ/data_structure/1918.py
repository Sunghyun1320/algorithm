import sys
input = sys.stdin.readline
###################################################
notation = input().rstrip()

n = len(notation)

stack = []
answer = ""

for char in range(n):
    if notation[char].isalpha():
        answer += notation[char]
        continue

    if notation[char] == "(":
        stack.append(notation[char])

    elif notation[char] == "*" or notation[char] == "/":
        while stack and (stack[-1] == '*' or stack[-1] == '/'):
            answer += stack.pop()
        stack.append(notation[char])

    elif notation[char] == "+" or notation[char] == "-":
        while stack and stack[-1] != '(':
            answer += stack.pop()
        stack.append(notation[char])
    elif notation[char] == ")":
        while stack and stack[-1] != '(':
            answer += stack.pop()
        stack.pop()

while stack:
    answer += stack.pop()

print(answer)




