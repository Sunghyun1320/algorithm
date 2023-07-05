import sys
sys.stdin = open("input.txt")
#############################################
def dfs(num, depth = 0):
    global count

    if count >= 50:
        return

    if depth == max_depth:
        return

    if int(num) <= n:
        count += 1
        answer.append(num + ".png")

    for i in range(10):
        dfs(num + str(i), depth + 1)




#############################################
T = int(input())

for test_case in range(1, T+1):
    n = input().rstrip()
    max_depth = len(n)
    n = int(n)

    print(f"#{test_case}", end=" ")

    count = 0
    answer = []

    for i in range(1, 10):
        dfs(str(i))

    print(" ".join(answer))
