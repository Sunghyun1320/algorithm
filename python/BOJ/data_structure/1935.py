import sys
input = sys.stdin.readline
###########################################
count_alpha = int(input())

order = input().rstrip()

num = []
for _ in range(count_alpha):
    num.append(int(input()))

###########################################
#입력받은 알파벳을 자신의 숫자로 반환하는 함수
def My_num(char):
    #이미 계산되어서 숫자가 들어있다면 숫자 반환
    if type(char) == int or type(char) == float:
        return char
    #아니라면 해당 알파벳의 숫자 반환
    else:
        index = ord(char) - ord('A')
        return num[index]

###########################################

stack = []
for i in range(len(order)):
    if order[i] == "+":
        num_2 = stack.pop(-1)
        num_1 = stack.pop(-1)
        stack.append(My_num(num_1) + My_num(num_2))

    elif order[i] == "-":
        num_2 = stack.pop(-1)
        num_1 = stack.pop(-1)
        stack.append(My_num(num_1) - My_num(num_2))

    elif order[i] == "*":
        num_2 = stack.pop(-1)
        num_1 = stack.pop(-1)
        stack.append(My_num(num_1) * My_num(num_2))

    elif order[i] == "/":
        num_2 = stack.pop(-1)
        num_1 = stack.pop(-1)
        stack.append(round(My_num(num_1) / My_num(num_2), 2))

    else:
        stack.append(order[i])

print(f"{stack[0]:.2f}")
    
    

