import sys
input = sys.stdin.readline
# 문제에서 주어진 최대 깊이를 기준으로
# 2분탐색으로 탐색하므로 log값 구하기
max_depth = 40000
LOG = 0
while True:
    if 2 ** LOG > max_depth:
        LOG += 1
        break

    LOG += 1

###########################################
n = int(input())

# 그래프 형태로 입력받기
graph = [[] for _ in range(n+1)]

for _ in range(n-1):
    a, b, distance = map(int, input().split())
    graph[a].append([b, distance])
    graph[b].append([a, distance])


###########################################
# 트리형태에서 부모노드와 자신의 레벨을 저장
tree = [[0 for _ in range(LOG)] for _ in range(n+1)]

visit = [1]
level = [-1 for _ in range(n+1)]
distance_list = [0 for _ in range(n+1)]
level[1] = 0

while visit:
    now = visit.pop()

    for next_node, distance in graph[now]:
        if level[next_node] != -1:
            continue

        level[next_node] = level[now] + 1
        distance_list[next_node] = distance_list[now] + distance
        tree[next_node][0] = now
        visit.append(next_node)


###########################################
# 2진 형태의 조상 노드 구하기
for i in range(1, LOG):
    for j in range(1, n+1):
        tree[j][i] = tree[tree[j][i - 1]][i - 1]

# for i in tree:
#     print(i)
###########################################
m = int(input())

for _ in range(m):
    a, b = map(int, input().split())

    distance_a = distance_list[a]
    distance_b = distance_list[b]

    # a의 레벨이 높도록 조절
    if level[a] < level[b]:
        a, b = b, a

    # 레벨 맞추기
    for i in range(LOG-1, -1, -1):
        if level[a] - level[b] >= 2 ** i:
            a = tree[a][i]

    if a == b:
        print(distance_a + distance_b - 2*distance_list[a])
        continue

    # 조상노드 찾기
    for i in range(LOG-1, -1, -1):
        if tree[a][i] != tree[b][i]:
            a = tree[a][i]
            b = tree[b][i]

    print(distance_a + distance_b - 2 * distance_list[tree[a][0]])
