import sys
input = sys.stdin.readline
from collections import deque
########################################
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
########################################
def find(a):
    if arr[a] != a:
        arr[a] = find(arr[a])

    return arr[a]


########################################
def union(a, b):
    a = find(a)
    b = find(b)

    if a == b:
        return False

    if a > b:
        arr[a] = b

    elif a < b:
        arr[b] = a

    return True


########################################
n, m = map(int, input().split())

graph = []

node = [[]]
# 그래프 입력받으며 S or K 인 위치 저장
for i in range(n):
    temp = list(input().rstrip())
    for j in range(n):
        if temp[j] == "K":
            node.append([i, j])
        elif temp[j] == "S":
            node[0] = [i, j]

    graph.append(temp.copy())

path = []

# 각각의 모든 S or K에서 BFS를 통해 모든 경로를 찾고 거리를 구함
for i in range(m+1):
    visited = [[False for _ in range(n)] for _ in range(n)]
    visit = deque()
    sx, sy = node[i]
    visit.append([sx, sy, 0])
    visited[sx][sy] = True

    while visit:
        x, y, distance = visit.popleft()

        for dir in range(4):
            nx = x + dx[dir]
            ny = y + dy[dir]

            if nx < 0 or nx >= n or ny < 0 or ny >= n or visited[nx][ny] or graph[nx][ny] == '1':
                continue

            visited[nx][ny] = True

            if graph[nx][ny] in "SK":
                path.append([sx, sy, nx, ny, distance + 1])

            visit.append([nx, ny, distance+1])

    # 만약 S를 기준으로 모든 K에 대한 경로를 찾았는데
    # 모든 K를 찾지 못했다면 -1 출력
    if i == 0 and len(path) != m:
        print(-1)
        exit()

# 거리를 기준으로 정렬
path.sort(key=lambda x: x[4])

# 크루스칼 적용
arr = [i for i in range(n**2)]

answer = 0
for sx, sy, nx, ny, distance in path:
    a = sx * n + sy
    b = nx * n + ny

    if union(a, b):
        answer += distance

print(answer)



