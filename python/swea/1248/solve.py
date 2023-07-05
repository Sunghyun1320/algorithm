import sys
sys.stdin = open("input.txt")
#################################################
t = int(input())

for test_case in range(1, t+1):
    # 데이터 입력받기
    count_node, count_load, node1, node2 = map(int, input().split())

    node_data = list(map(int, input().split()))

    # tree구조 저장
    # index : node, [0] :  부모노드 [1] : 자식 노드 리스트
    tree = [[0, []] for _ in range(count_node+1)]

    # 입력받은 데이터대로 tree구조 생성
    for i in range(count_load):
        tree[node_data[i * 2 + 1]][0] = node_data[i * 2]
        tree[node_data[i * 2]][1].append(node_data[i * 2 + 1])

    # node1과 node2의 경로 저장
    # 서로 다른 경로를 탐색할 경우 이전 노드가 공통조상
    # 아예 같은 경로일 때를 대비해서 [0]에 서로 다른 값 저장
    node1_path = [-1, node1]
    node2_path = [-2, node2]

    # node1에서 부모노드를 찾아가며 노드 추가
    node = node1
    while True:
        # 1의 부모노드는 0으로 저장되어 있으므로
        # root_node에서 부모노드를 탐색시도하면 스톱
        if node == 0:
            break

        node1_path.append(tree[node][0])
        node = tree[node][0]

    # node2에서 부모노드를 찾아가며 노드 추가
    node = node2
    while True:
        # 1의 부모노드는 0으로 저장되어 있으므로
        # root_node에서 부모노드를 탐색시도하면 스톱
        if node == 0:
            break

        node2_path.append(tree[node][0])
        node = tree[node][0]

    # 역으로 경로를 찾기위해 index레벨 통일
    node1_idx = len(node1_path) - 1
    node2_idx = len(node2_path) - 1

    while True:
        # 서로 다른 경로를 찾으면 이전의 같은 경로인 node를 answer_node에 저장하고
        # 멈춤
        if node1_path[node1_idx] != node2_path[node2_idx]:
            answer_node = node1_path[node1_idx + 1]
            break

        # 같은 경로이면 다음 노드 탐색
        node1_idx -= 1
        node2_idx -= 1

    # dfs를 위한 stack
    stack = [answer_node]
    # 공통 조상을 기준으로 자식노드의 개수를 세는 변수
    count = 0

    # dfs를 통해 자식노드를 탐색하며 개수 추가
    while stack:
        node = stack.pop()
        count += 1

        for next_node in tree[node][1]:
            stack.append(next_node)

    # 결과 출력
    print(f"#{test_case} {answer_node} {count}")

