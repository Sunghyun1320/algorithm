import sys
input = sys.stdin.readline
####################################
# import heapq
#
# # 집과 간선의 개수 받아오기
# n, m = map(int, input().split())
#
# # 그래프 만들기
# graph = [[] for _ in range(n+1)]
#
# for _ in range(m):
#     a, b, c = map(int, input().split())
#
#     if a == b:
#         continue
#
#     graph[a].append([b, c])
#     graph[b].append([a, c])
#
# # 최소 간선을 선택하기 위한 최소 힙
# heap = []
# # 방문여부를 체크하기 위한 visited
# visited = [False for _ in range(n+1)]
# # 시작지점을 1로 설정
# heapq.heappush(heap, [0, 1])
# # 집의 개수와 MST의 유지비, 최대 유지비
# count = 0
# sum_cost = 0
# max_cost = -1
#
# # MST 찾기
# while heap:
#     # 집의 개수가 n개가 되면 종료
#     if count == n:
#         break
#
#     cost, node = heapq.heappop(heap)
#
#     # 이미 방문한 집이면 패스
#     if visited[node]:
#         continue
#
#     # 방문처리 후
#     visited[node] = True
#     count += 1
#     sum_cost += cost
#     max_cost = max(max_cost, cost)
#
#     # 현재 노드에서 갈수있는 집들 중 방문 안한 곳 힙에 추가
#     for next_node, new_cost in graph[node]:
#         if visited[next_node]:
#             continue
#
#         heapq.heappush(heap, [new_cost, next_node])
#
# # MST에서 최대 유지비 1개만 제거
# print(sum_cost - max_cost)
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

# 노드 전체 입력받기
node = [list(map(int, input().split())) for _ in range(m)]

# 거리 기준으로 정렬
node.sort(key=lambda x: x[2])

# 크루스칼 진행
arr = [i for i in range(n+1)]

# MST 가중치 합
sum_cost = 0
# MST 가중치 최대값
max_cost = -1
for a, b, cost in node:
    if union(a, b):
        sum_cost += cost
        max_cost = max(max_cost, cost)

# MST에서 최대가중치 빼서 출력
print(sum_cost - max_cost)

