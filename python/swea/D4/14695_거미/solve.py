import sys
sys.stdin = open("input.txt")
#############################################
T = int(input())

for test_case in range(1, T+1):
    n = int(input())

    if n <= 3:
        print(f"#{test_case} TAK")
        for _ in range(n):
            input()
        continue

    m = [[1 for _ in range(4)] for _ in range(3)]
    for i in range(3):
        temp = list(map(int, input().split()))
        for j in range(3):
            m[i][j] = temp[j]







    # a =
    # b =
    # c =
    # d = a * m[0][0] + b * m[0][1] + c * m[0][2]


