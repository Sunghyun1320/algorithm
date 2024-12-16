import sys
input = sys.stdin.readline
# sys.setrecursionlimit(10**6)
###########################################
def check_max(before_select = False, now = 1):
    # 자식 노드가 없는 리프 노드면
    if len(tree[now]) == 0:
        # 부모노드가 선택되었으면 자신은 선택 못함
        if before_select:
            return 0, []
        # 부모노드가 선택되지 않았으면 자신을 선택
        else:
            return node_value[now], [now]

    # 이번 노드를 선택 안했을 때 최대값과  선택된 형태
    False_max = 0
    False_select = []

    # 이번 노드를 선택 했을 때 최대값과 선택된 형태
    True_max = node_value[now]
    True_select = [now]

    # 모든 자식들에 대해서
    for child in tree[now]:
        # 이번 노드를 선택하지 않았을 때 최대값 찾아보기
        value, select = check_max(False, child)
        False_max += value
        False_select += select

        # 부모 노드가 선택되지 않았으면, 이번 노드를 선택해서 최대값 찾아보기
        if not before_select:
            value, select = check_max(True, child)
            True_max += value
            True_select += select

    # 부모노드가 선택되었으면 선택되지 않은 경우만 보내기
    if before_select:
        return False_max, False_select

    # 부모노드가 선택되지 않았으면 둘중 클 때의 상태를 반환하기
    if False_max >= True_max:
        return False_max, False_select
    else:
        return True_max, True_select


###########################################
n = int(input())

node_value = [0] + list(map(int, input().split()))

###########################################
# 부모자식이 정의 안된채로 주어지므로 그래프로 저장
graph = [[] for _ in range(n+1)]

for _ in range(n-1):
    a, b = map(int, input().split())

    graph[a].append(b)
    graph[b].append(a)

###########################################
# 루트노드를 1로해서 트리 형태로 다시 저장
visit = [1]
visited = [False for _ in range(n+1)]
visited[1] = True

tree = [[] for _ in range(n+1)]

while visit:
    now = visit.pop()

    for next_node in graph[now]:
        if visited[next_node]:
            continue

        visited[next_node] = True
        tree[now].append(next_node)
        visit.append(next_node)

# for i in tree:
#     print(i)
###########################################

answer, select = check_max()
select.sort()

print(answer)
print(*select)



