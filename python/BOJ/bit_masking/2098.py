import sys
input = sys.stdin.readline
##############################################
# 현재 노드와 현재까지의 경로를 비트마스킹으로 표현
def dfs(node = 0, visited = 1):
    # 모든 노드를 방문했으면 0으로 돌아 갈 수 있는지 체크
    if visited == (1 << n) - 1:
        if cost_list[node][0]:
            return cost_list[node][0]
        else:
            return INF

    # 이미 최단경로가 추측되어 있으면 그 경로 반환
    if dp[node][visited] != -1:
        return dp[node][visited]

    # 남은 경로의 최소값을 저장할 변수
    min_set = INF
    # 모든 노드에 대해서
    for next_node in range(1, n):
        # 방문을 했다면 패스
        if visited & (1 << next_node):
            continue

        # 길이 없다면 패스
        if cost_list[node][next_node] == 0:
            continue

        min_set = min(min_set,
                    dfs(next_node, visited | (1 << next_node)) + cost_list[node][next_node])

    dp[node][visited] = min_set

    return dp[node][visited]

##############################################
INF = int(1e9)

n = int(input())

cost_list = [list(map(int, input().split())) for _ in range(n)]

dp = [[-1 for _ in range(1 << n)] for _ in range(n)]

dfs()
print(dp[0][1])