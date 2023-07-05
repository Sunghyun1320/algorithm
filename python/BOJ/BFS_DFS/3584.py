import sys
input = sys.stdin.readline
###################################################
# 경로를 찾는 함수
def Find_path_node(a, root_node):
    node = a
    root_node = root_node
    path = [0, a]
    while True:
        if node == root_node:
            break

        path.append(tree[node])
        node = tree[node]

    return path


###################################################
t = int(input())
for test_case in range(t):
    n = int(input())

    # 각 인덱스의 자신의 부모노드를 저장함
    tree = [0 for _ in range(n+1)]

    # 간선을 입력받아 트리로 저장
    for __ in range(n - 1):
        a, b = map(int, input().split())
        tree[b] = a

    # 루트노드를 찾아줌
    for i in range(1, n+1):
        if tree[i] == 0:
            root_node = i
            break

    # 공통조상을 찾아야할 두 노드
    a, b = map(int, input().split())
    if a == b:
        print(a)
        continue

    path_a = Find_path_node(a, root_node)
    path_b = Find_path_node(b, root_node)

    index_a = len(path_a) - 1
    index_b = len(path_b) - 1

    while True:
        if path_a[index_a] != path_b[index_b]:
            break
        index_a -= 1
        index_b -= 1

    print(path_a[index_a + 1])

