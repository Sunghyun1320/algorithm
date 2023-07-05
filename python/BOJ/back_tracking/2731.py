import sys
input = sys.stdin.readline
#############################################
def solve(num, depth = 1):
    num_3 = num*num*num

    # 정답을 찾은경우 출력 후 리턴
    if list(map(int, list(str(num_3))[len(str(num_3)) - length:])) == input_data:
        print(num)
        return

    # 0~9까지 숫자를 체크
    # (a+b)^3 = a^3 + 3a^2b + 3ab^2 + b^3
    # 여기서 a는 a*10^depth 이므로 depth에 해당하는 자리수는
    # 3ab^2 + b^3 에 의해서만 결정된다
    for i in range(10):
        # b^3 에서 depth에 해당하는 자리수 찾기
        b_3 = (num_3 % int(10**(depth+1))) // int(10**depth)
        # 3ab^2에서 depth에 해당하는 자리수 찾기
        # 여기서 i는 i*10^depth 이므로 3ib^2 * 10^depth
        # 즉 3ib^2의 1의 자리가 depth에 해당하는 자리수
        a_2_b = (i*num*num*3) % 10

        if (b_3 + a_2_b) % 10 == input_data[length-depth-1]:
            solve(i*(10**depth) + num, depth+1)


#############################################
n = int(input())

for _ in range(n):
    int_num = int(input())
    input_data = list(map(int, list(str(int_num))))
    length = len(input_data)

    # 1의 자리 숫자에 따라 답의 1의 자리수는 결정됨
    if input_data[-1] == 1:
        solve(1)

    elif input_data[-1] == 3:
        solve(7)

    elif input_data[-1] == 7:
        solve(3)

    elif input_data[-1] == 9:
        solve(9)