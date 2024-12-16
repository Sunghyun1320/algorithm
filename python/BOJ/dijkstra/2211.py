import sys, heapq
input = sys.stdin.readline
#########################################
INF = int(1e9)
#########################################
n, m = map(int, input().split())

computer = [[] for _ in range(n+1)]

for _ in range(m):
    a, b, c = map(int, input().split())
    # 혹시나 같은 컴퓨터끼리 연결시 경로 추가 안함
    if a == b:
        continue

    computer[a].append([b, c])
    computer[b].append([a, c])

# 다익스트라 기본 변수들
visit = []
distance = [INF for _ in range(n+1)]
# 이번엔 복구하는 경로를 알아야 하므로 경로도 저장
path_list = [[] for _ in range(n+1)]
distance[1] = 0

# 거리와, 노드, 경로를 저장
heapq.heappush(visit, [0, 1, [1]])

# 다익스트라 시작
while visit:
    cost, node, path = heapq.heappop(visit)

    for next_node, next_cost in computer[node]:
        # 거리 갱신 실패시 다음 노드 체크
        if distance[next_node] <= cost + next_cost:
            continue

        # 거리 갱신시 경로 갱신과 힙에 거리, 노드, 경로 추가
        distance[next_node] = cost + next_cost
        path_list[next_node] = path + [next_node]
        heapq.heappush(visit, [cost+next_cost, next_node, path + [next_node]])

# 경로가 출력됐는지 체크하는 딕셔너리
check = {}
# 경로의 개수
count = 0
# n번까지 컴퓨터에 대해서
for i in range(1, n+1):
    # 복구한 경로들이
    for j in range(len(path_list[i]) - 1):
        # 이미 있는 경로면 pass
        if check.get(",".join([str(path_list[i][j]), str(path_list[i][j+1])]), False):
            continue

        # 없는 경로면 추가후, 개수 추가
        check[",".join([str(path_list[i][j]), str(path_list[i][j+1])])] = True
        count += 1

# 개수 출력후
print(count)
# 딕셔너리의 키값을 출력
for i in check.keys():
    print(i.replace(",", " "))
