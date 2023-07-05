import sys
input = sys.stdin.readline
##############################################
def dfs(n, m, select, depth = 0, answer = []):
    if m == depth:
        temp = ",".join(list(map(str, answer)))
        if check.get(temp, False):
            return

        check[temp] = True
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
check = {}

dfs(n, m, [False for _ in range(n)])