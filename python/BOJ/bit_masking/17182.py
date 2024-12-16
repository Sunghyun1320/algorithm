import sys
input = sys.stdin.readline
#################################################
def solve(node, depth = 0, cost = 0):
    global answer

    if cost >= answer:
        return

    if depth == n - 1:
        answer = min(answer, cost)
        return

    for next_node in range(n):
        if visited[next_node]:
            continue

        visited[next_node] = True
        solve(next_node, depth+1, cost + cost_data[node][next_node])
        visited[next_node] = False


#################################################
INF = int(1e9)
n, k = map(int, input().split())

cost_data = [list(map(int, input().split())) for _ in range(n)]

for mid in range(n):
    for start in range(n):
        for end in range(n):
            cost_data[start][end] = min(cost_data[start][end], cost_data[start][mid] + cost_data[mid][end])

visited = [False for _ in range(n)]
visited[k] = True

answer = INF
solve(k)

print(answer)

