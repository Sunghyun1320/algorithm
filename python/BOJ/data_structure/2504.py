import sys
input = sys.stdin.readline
##########################################
input_data = input().rstrip()

stack = []
temp = 1
result = 0

# 인덱스 접근
for i in range(len(input_data)):
    # 괄호가 열리면 숫자만큼 곱해주고 스택에 추가
    if input_data[i] == "(":
        temp *= 2
        stack.append("(")

    elif input_data[i] == "[":
        temp *= 3
        stack.append("[")

    # 괄호가 닫힐 때
    elif input_data[i] == ")":
        # 스택의 마지막이 다른 괄호면 틀림
        if len(stack) == 0 or stack[-1] == "[":
            result = 0
            break

        # 단일 괄호로 숫자이면 결과에 더하기
        if input_data[i-1] == "(":
            result += temp

        # 쌍에 이상없는 괄호면 나눠주기
        temp //= 2
        stack.pop(-1)

    # 괄호가 닫힐 때
    elif input_data[i] == "]":
        # 스택의 마지막이 다른 괄호면 틀림
        if len(stack) == 0 or stack[-1] == "(":
            result = 0
            break

        # 단일 괄호로 숫자이면 결과에 더하기
        if input_data[i - 1] == "[":
            result += temp

        # 쌍에 이상없는 괄호면 나눠주기
        temp //= 3
        stack.pop(-1)

if len(stack) != 0:
    result = 0

print(result)