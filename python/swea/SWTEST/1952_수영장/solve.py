import sys
sys.stdin = open("input.txt")
#############################################
def solve(depth = 0, cost = 0):
    global answer
    if depth >= 12:
        answer = min(answer, cost)
        return

    if cost >= answer:
        return

    # 1일권 이용시
    solve(depth + 1, cost + plan[depth] * day)

    # 1개월권 이용시
    solve(depth + 1, cost + month)

    # 3개월권 이용시
    solve(depth + 3, cost + three_month)


#############################################
T = int(input())

for test_case in range(1, T+1):
    day, month, three_month, year = map(int, input().split())
    plan = list(map(int, input().split()))

    answer = year

    solve()

    print(f"#{test_case} {answer}")
