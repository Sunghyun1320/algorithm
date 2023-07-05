import sys
input = sys.stdin.readline
##############################################
# 괄호 쌍 중 제거할 괄호쌍을 고른 조합을 만드는 함수
# 제거할 괄호쌍은 0 유지할 괄호쌍은 1
def Make_combination_dfs(depth = 0, combination = []):

    # if depth == len(couple_bracket):
    #     Make_answer(combination)
    #     return
    #
    # for i in range(2):
    #     combination.append(i)
    #     Make_combination_dfs(depth + 1, combination)
    #     combination.pop(-1)

    #######################################################

    # dfs가 아니라 조합으로 정답 구하기
    n = len(couple_bracket)

    for i in range((1 << n) - 1):
        temp = bin(i)[2:]
        combination = "0" * (n-len(temp)) + temp
        Make_answer(combination)

##############################################
# 제거, 유지가 확정된 조합으로 정답을 만들 함수
def Make_answer(combination):
    # 제거가 없는 조합은 무시
    # if 0 not in combination:
    #     return

    global answer
    string = list(input_data)
    for i in range(len(combination)):
        if combination[i] == '0':
            string[couple_bracket[i][0]] = None
            string[couple_bracket[i][1]] = None

    temp = ""
    for char in string:
        if char != None:
            temp += char
    if temp not in answer:
        answer.append(temp)


##############################################
# 연산 시작
input_data = input().rstrip()

# 괄호 쌍을 찾는 스택
stack = []
# 괄호 쌍을 저장하는 리스트
couple_bracket = []
# 정답을 저장하는 리스트
answer = []

# 데이터를 순회하며 괄호 쌍을 찾음
for index in range(len(input_data)):
    # 괄호가 열리면 stack에 index저장
    if input_data[index] == "(":
        stack.append(index)
    # 괄호가 닫히면 마지막에 열린 괄호(괄호 쌍)의 인덱스와 함께 저장
    elif input_data[index] == ")":
        # 괄호 쌍을 저장한다.
        couple_bracket.append([stack.pop(-1), index])

# dfs실행
Make_combination_dfs()


# 사전 순으로 정렬 (아스키 코드의 숫자를 기준으로)
answer.sort()

for ans in answer:
    print(ans)




