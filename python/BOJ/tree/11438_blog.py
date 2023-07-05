import sys
from collections import defaultdict
from collections import deque

input = sys.stdin.readline
LOG = 21


def bfs(s):
    global V
    que = deque()
    que.append(s)
    depth[s] = 1

    while que:
        cur = que.popleft()
        for nxt in graph[cur]:
            if depth[nxt]: continue

            depth[nxt] = depth[cur] + 1
            par[nxt][0] = cur
            que.append(nxt)


def set_parent(V):
    # 이중 for문 순서 중요!!
    for num in range(1, LOG):
        for nd in range(1, V + 1):
            par[nd][num] = par[par[nd][num - 1]][num - 1]


def LCA(a, b):
    # a를 더 깊게
    if depth[b] > depth[a]:
        a, b = b, a

    # 높이 같아지게 a 올라옴
    for i in range(LOG - 1, -1, -1):
        if (depth[a] - depth[b]) & (1 << i) == (1 << i):
            a = par[a][i]

    if a == b:
        return a

    # 공통조상까지 같이 jump
    for i in range(LOG - 1, -1, -1):
        if par[a][i] != par[b][i]:
            a = par[a][i]
            b = par[b][i]

    return par[a][0]


if __name__ == "__main__":
    V = int(input())

    graph = defaultdict(list)
    for _ in range(V - 1):
        a, b = map(int, input().rstrip().split())
        graph[a].append(b)
        graph[b].append(a)

    depth = [0 for _ in range(V + 1)]
    par = [[0 for _ in range(LOG)] for _ in range(V + 1)]

    # dfs(1, 1)
    bfs(1)
    set_parent(V)

    Q = int(input())
    for _ in range(Q):
        a, b = map(int, input().rstrip().split())
        answer = LCA(a, b)
        print(answer)