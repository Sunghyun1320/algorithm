import sys
sys.stdin = open("input.txt")
#############################################
def cal_dfs(num, plus, minus, multi, divide, depth = 1):
    if depth == n:
        global min_answer, max_answer
        min_answer = min(min_answer, num)
        max_answer = max(max_answer, num)
        return

    if plus:
        cal_dfs(num + nums[depth], plus - 1, minus, multi, divide, depth + 1)

    if minus:
        cal_dfs(num - nums[depth], plus, minus - 1, multi, divide, depth + 1)

    if multi:
        cal_dfs(num * nums[depth], plus, minus, multi - 1, divide, depth + 1)

    if divide:
        cal_dfs(int(num / nums[depth]), plus, minus, multi, divide - 1, depth + 1)




#############################################

T = int(input())

for test_case in range(1, T+1):
    n = int(input())
    plus, minus, multi, divide = map(int, input().split())
    nums = list(map(int, input().split()))

    min_answer = int(1e9)
    max_answer = -int(1e9)

    cal_dfs(nums[0], plus, minus, multi, divide)

    print(f"#{test_case} {max_answer - min_answer}")

