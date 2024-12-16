import sys
sys.stdin = open("input.txt")
#############################################
T = int(input())

for test_case in range(1, T+1):
    n, k = map(int, input().split())
    if k == 2 or k == 4 or k == n:
        print(f"#{test_case} -1")
        continue

    check = False
    for i in range(2, k, 2):
        if k % i != 0:
            for j in range(i + 2, n+1, 2):
                if j % i == 0:
                    check = True
                    break
        if check:
            break

    if check:
        answer = "("*((n-j)//2) + ("("*(i//2) + ")"*(i//2)) * 2 + ")"*((n-j)//2)
        print(f"#{test_case} {answer}")

    else:
        print(f"#{test_case} -1")



