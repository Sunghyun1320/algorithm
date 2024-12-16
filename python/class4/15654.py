import sys
input = sys.stdin.readline
##############################################
def dfs(n, m, select, depth = 0, answer = []):
    if m == depth:
        print(*answer)
        return

    for i in range(0, n):
        if select[i]:
            continue

        select[i] = True
        dfs(n, m, select, depth+1, answer + [data[i]])
        select[i] = False

##############################################
n, m = map(int, input().split())
data = list(map(int, input().split()))
data.sort()



dfs(n, m, [False for _ in range(n)])