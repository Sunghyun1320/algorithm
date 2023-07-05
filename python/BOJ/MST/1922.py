import sys
input = sys.stdin.readline
import heapq
######################################
# 컴퓨터의 개수
computer_count = int(input())
# 연결된 간선의 개수
line_count = int(input())

# 컴퓨터의 연결상태를 저장하는 그래프
graph = [[] for _ in range(computer_count+1)]

# line_count개수만큼 간선을 입력받아 저장
for _ in range(line_count):
    a, b, c = map(int, input().split())

    # 같을경우 저장안함
    if a == b:
        continue

    graph[a].append([b, c])
    graph[b].append([a, c])

# 방문여부 체크용 visited
visited = [False for _ in range(computer_count+1)]

# 각 비용이 저장되며 비용의 최소값을 구하는 최소힙
heap = []
# 시작지점으로 1 넣어주기
heapq.heappush(heap, (0, 1,))
# 연결된 컴퓨터의 개수
count = 0

# 현재까지 연결된 간선의 비용 합
answer = 0
while True:
    # 연결된 컴퓨터의 개수가 일치하면 종료
    if count == computer_count:
        break
    
    # 비용과 컴퓨터 받아오기
    cost, node = heapq.heappop(heap)
    # 이전에 방문한 컴퓨터이면 넘어가기
    if visited[node]:
        continue

    # 방문처리후
    visited[node] = True

    # 비용합치고 연결된 컴퓨터 개수 추가
    answer += cost
    count += 1
    
    # 현재 컴퓨터와 연결된 모든 컴퓨터 heapq에 저장하기
    for next_node, new_cost in graph[node]:
        if visited[next_node]:
            continue

        heapq.heappush(heap, [new_cost, next_node])

# 결과 출력
print(answer)