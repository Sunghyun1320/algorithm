import sys
input = sys.stdin.readline
###################################################
# 트리에서 각각 자신의 부모를 저장하는 함수
def make_parents():
    visit = [1]
    tree[1] = 0

    while visit:
        now = visit.pop()

        for next_node in node[now]:
            # 부모노드를 이미 찾은(방문한 노드면) 패스
            if tree[next_node] != -1:
                continue

            # 다음 노드의 부모노드는 현재 노드임을 저장
            tree[next_node] = now
            visit.append(next_node)


###################################################
def make_path(goal):
    # 이전에 경로를 탐색했으면 결과만 반환
    if parents[goal] is not None:
        return parents[goal]

    # 그게 아니면 부모노드를 타고 올라가며 경로를 반환
    path = []

    now = goal
    while True:
        if now == 0:
            break

        path.append(now)
        now = tree[now]

    return path
###################################################

n = int(input())

# 간선 정보 그대로 입력받기
node = [[] for _ in range(n+1)]

for _ in range(n-1):
    a, b = map(int, input().split())

    node[b].append(a)
    node[a].append(b)


###################################################
# 트리에서 자신의 부모 노드를 따로 저장
tree = [-1 for _ in range(n+1)]
make_parents()

#############################################################
m = int(input())
parents = [None for _ in range(n+1)]
for _ in range(m):
    a, b = map(int, input().split())

    # 경로를 탐색해서 저장
    parents[a] = make_path(a)
    parents[b] = make_path(b)

    len_a = len(parents[a])
    len_b = len(parents[b])

    # 레벨 초기화
    i = len_a - 1
    j = len_b - 1

    while True:
        # 둘중 하나라도 모든 경로를 탐색했다면
        # 이전 값이 공통 조상
        if i == -1 or j == -1:
            print(parents[a][i+1])
            break

        # 경로가 달라졌으면
        # 이전 값이 공통 조상
        if parents[a][i] != parents[b][j]:
            print(parents[a][i+1])
            break

        # 경로가 같으면 다음 경로 확인
        if parents[a][i] == parents[b][j]:
            i -= 1
            j -= 1











