import sys
sys.stdin = open("input.txt")
#############################################
T = int(input())

for test_case in range(1, T+1):
    a, b = map(int, input().split())

    m = "0b"+"1" * a + "0" * b
    n = "0b1" + "0"*b + "1"*(a-1)

    answer = int(m, 2) * int(n, 2)

    answer = bin(answer)

    print(f'#{test_case} {answer.count("1")}')


