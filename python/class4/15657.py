import sys
input = sys.stdin.readline
##############################################
def dfs(n, m, before_i, depth = 0, answer = []):
    if m == depth:
        print(*answer)
        return

    for i in range(before_i, n):
        dfs(n, m, i, depth+1, answer + [data[i]])

##############################################
n, m = map(int, input().split())
data = list(map(int, input().split()))
data.sort()


dfs(n, m, 0)