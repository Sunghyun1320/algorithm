import  sys
input = sys.stdin.readline
######################################################
input_data = input().rstrip()


stick = 1
answer = 0

#시작은 항상 괄호가 열렸다고 생각
#그래서 stick와 answer이 1로 시작
for i in range(1, len(input_data)):

    #괄호가 열리면 현재 스틱 1개 추가
    if input_data[i] == "(":
        stick += 1

    #괄호가 닫혔을때
    elif input_data[i] == ")":
        #그 괄호가 레이저 괄호이면 잘려진 막대 추가
        if input_data[i-1] == "(":
            stick -= 1
            answer += stick

        #그 막대가 막대 괄호이면 막대개수 1감소
        #막대의 마지막 파츠 1개 추가
        else:
            stick -= 1
            answer += 1


print(answer)