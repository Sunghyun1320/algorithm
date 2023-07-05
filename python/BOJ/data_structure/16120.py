import sys
input_ = sys.stdin.readline
##########################################
input_data = input_().rstrip()

stack = []

# 이전 값이 A인지 체크하는 변수
check = False
# 각 문자열로 체크
for char in input_data:
    if check and char == "A":
        print("NP")
        exit()

    # 문자열이 A이면
    if char == "A":
        # 앞의 PP를 빼옴
        try:
            a = stack.pop(-1)
            b = stack.pop(-1)

        # PP가 없으면 PPAP아님
        except IndexError:
            print("NP")
            exit()

        check = True
        continue

    # P는 추가 -> A가 나와서 PPAP가 하나의 P로 바뀜
    # PP는 빠지고 A는 추가 안함 뒤의 P가 추가됨
    check = False
    stack.append(char)

# 마지막이 A로 끝났으면 NP 아니면 PPAP
if check:
    print("NP")
elif stack == ["P"]:
    print("PPAP")
else:
    print("NP")
