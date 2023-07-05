import sys
input = sys.stdin.readline
##############################################
def dfs(n, m, before_i, depth = 0, answer = []):
    if m == depth:
        print(*answer)
        return

    for i in range(before_i+1, n+1):
        dfs(n, m, i, depth+1, answer + [i])

##############################################
n, m = map(int, input().split())

dfs(n, m, 0)