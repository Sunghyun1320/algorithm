import sys
input = sys.stdin.readline
from collections import deque
#############################################
n, k = map(int, input().split())

# 시작점과 거리를 초기값으로 저장
visit = deque()
visit.append((n, n, 0))

# 방문 여부를 판단하는 배열
# [0]은 이전에 방문한 칸, [1]은 거리
visited = [(-1, 100001) for _ in range(100001)]

# 정답이 저장될 두 변수
ans_dis = 100001
# ans_count = 0

# 다음 탐색한 장소가 있을 때 순환
while visit:
    x, back_x, dis = visit.popleft()
    # 현재 도달 방식이 현재 저장된 방법보다 최단 거리면, 이전 위치와 거리 저장
    # 초기값은 -1, 100001
    if visited[x][1] > dis:
        visited[x] = (back_x, dis)


    # 목적지 탐색 시 거리와 개수 +1
    if x == k and ans_dis > dis:
        ans_dis = dis
        break

    # 현재 장소에서 이동가능하고, 이전에 방문하지 않은 모든 칸 추가
    # 이동가능한 칸과 현재칸, 거리 +1해서 추가
    if 0 <= x+1 <= 100000 and visited[x+1][0] == -1:
        visit.append((x+1, x, dis+1))

    if 0 <= x-1 <= 100000 and visited[x-1][0] == -1:
        visit.append((x-1, x, dis+1))

    if x < k and 0 <= x*2 <= 100000 and visited[x*2][0] == -1:
        visit.append((x*2, x, dis+1))

print(ans_dis)

ans_path = deque()
while True:
    if n == x:
        ans_path.appendleft(n)
        break

    ans_path.appendleft(x)
    x = visited[x][0]

print(*ans_path)