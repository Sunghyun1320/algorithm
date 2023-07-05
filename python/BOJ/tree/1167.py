import sys
input = sys.stdin.readline
##################################################
n = int(input())

# 트리 노드
node = [[] for _ in range(n+1)]

# 간선정보에 맞춰 트리 정보 갱신하기
for _ in range(n):
    edge_data = list(map(int, input().split()))

    i = 1
    while True:
        if edge_data[i] == -1:
            break

        node[edge_data[0]].append([edge_data[i], edge_data[i+1]])
        i += 2

# 1부터 시작해서 최대깊이 노드 찾아냄
visit = [[1, 0]]
visited = [False for _ in range(n+1)]
visited[1] = True

max_depth = 0
max_depth_node = 1
# dfs시작
while visit:
    now, depth = visit.pop()

    if depth > max_depth:
        max_depth = depth
        max_depth_node = now

    for next_node, distance in node[now]:
        if visited[next_node]:
            continue

        visited[next_node] = True
        visit.append([next_node, depth + distance])


# 최대깊이 지점에서 다시 최대깊이 지점 찾기
visit = [[max_depth_node, 0]]
visited = [False for _ in range(n+1)]
visited[max_depth_node] = True

max_depth = 0
max_depth_node = 1
# dfs찾기
while visit:
    now, depth = visit.pop()

    if depth > max_depth:
        max_depth = depth
        max_depth_node = now

    for next_node, distance in node[now]:
        if visited[next_node]:
            continue

        visited[next_node] = True
        visit.append([next_node, depth + distance])

print(max_depth)


