import sys
from copy import deepcopy
input = sys.stdin.readline
###############################################################
# dfs용 함수
def dfs(start_node):
    global position, tree_picture

    visit = [start_node]
    visited = [0 for _ in range(n+1)]
    level = 0

    while visit:
        node = visit.pop()

        # 자식 노드가 없으면 다시 돌아감
        if node == -1:
            level -= 1
            continue

        # 다음 레벨 도달시 새로운 레벨 추가
        else:
            if len(tree_picture) <= level:
                tree_picture.append(deepcopy(level_data))

        # 이미 방문한 노드면?
        # 오른쪽 노드 탐색이 완료된 상태
        # 자신을 기록하고 다음 왼쪽노드 탐색 시작
        if visited[node] == 1:
            tree_picture[level][0][position] = node

            # 기록시 해당 레벨의 최 좌측, 최 우측 위치 갱신
            if tree_picture[level][1] > position:
                tree_picture[level][1] = position

            if tree_picture[level][2] < position:
                tree_picture[level][2] = position

            # 위치 + 1
            position += 1
            # 오른쪽 탐색완료 표시
            visited[node] += 1
            level += 1

            continue

        # 왼쪽 탐생이 끝난 상태이면
        elif visited[node] == 2:
            # 레벨 낮춰서 돌아감
            level -= 1
            continue

        # 방문 노드 아니면 방문처리
        visited[node] += 1


        # 이 장소에 새로 오는거면 다음 경로들 추가

        # 왼쪽 노드 추가
        visit.append(node)
        visit.append(tree[node][1][1])
        # 오른쪽 노드가 탐색 완료되었는지 판단하기 위한 자신 추가
        visit.append(node)
        # 오른쪽 먼저 탐색하기 위해서 오른쪽을 나중에
        visit.append(tree[node][1][0])
        level += 1


###############################################################
n = int(input())

tree = [[-1, [0, 0]] for _ in range(n+1)]

# 트리 입력받기
for i in range(n):
    n1, a, b = map(int, input().split())
    tree[n1][1] = [a, b]
    if a != -1:
        tree[a][0] = n
    if b != -1:
        tree[b][0] = n

# 루트노드 찾기
root_node = 0
for i in range(1, n+1):
    if tree[i][0] == -1:
        root_node = i
        break

# print("root_node : ", root_node)
position = 0

# 각 레벨의 데이터 레벨의 모습과, 최 좌측, 최 우측이 저장됨
level_data = [[0 for _ in range(n)], n, -1]

# 0 레벨 상태 추가하기
tree_picture = [deepcopy(level_data)]

# 깊이 0, 1번 노드부터 dfs시작
dfs(root_node)

# for i in tree_picture:
#     print(i)

# 각 레벨의 최대 너비 탐색 및 갱신
max_length = 0
max_level = 0
for i in range(len(tree_picture)):
    if max_length < tree_picture[i][2] - tree_picture[i][1] + 1:
        max_length = tree_picture[i][2] - tree_picture[i][1] + 1
        max_level = i+1

print(max_level, max_length)
