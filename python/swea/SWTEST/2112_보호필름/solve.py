import sys
sys.stdin = open("input.txt")
#############################################
def check():
    for j in range(W):
        check = False
        num = graph[0][j]
        count = 0
        for i in range(D):
            if num == graph[i][j]:
                count += 1
            else:
                if count >= K:
                    check = True
                    break
                num = graph[i][j]
                count = 1

        if count >= K:
            check = True

        if not check:
            return False

    return True


#############################################
def dfs(depth=0, index=0):
    global answer
    if answer <= depth:
        return

    if check():
        answer = min(depth, answer)
        return

    if depth == K:
        return

    for i in range(index, D):
        temp = graph[i].copy()

        for j in range(W):
            graph[i][j] = 0

        dfs(depth + 1, i + 1)

        for j in range(W):
            graph[i][j] = 1

        dfs(depth + 1, i + 1)

        graph[i] = temp



#############################################
T = int(input())

for test_case in range(1, T+1):
    D, W, K = map(int, input().split())
    graph = [list(map(int, input().split())) for _ in range(D)]
    answer = int(1e9)
    dfs()
    print(f"#{test_case} {answer}")

