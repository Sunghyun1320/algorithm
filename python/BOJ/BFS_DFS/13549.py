import sys
input = sys.stdin.readline
from collections import deque
#############################################
n, k = map(int, input().split())

# 시작점과 거리를 초기값으로 저장
visit = deque()
visit.append((n, 0))

# 방문 여부를 판단하는 배열
visited = [False for _ in range(100001)]
visited[n] = True

# 정답이 저장될 두 변수
ans_dis = 100001
# ans_count = 0

# 다음 탐색한 장소가 있을 때 순환
while visit:
    x, dis = visit.popleft()
    # 현재 위치 방문 처리
    visited[x] = True
    # 최단거리 이상의 거리는 탐색할 필요 없으므로 반복 중단
    # if ans_dis < dis:
    #     break

    # 목적지 탐색시 거리와 개수 +1
    if x == k and ans_dis > dis:
        ans_dis = dis
        # ans_count += 1


    # if ans_dis == dis:
    #     continue

    # 현재 장소에서 이동가능하고, 이전에 방문하지 않은 모든 칸 추가
    if 0 <= x+1 <= 100000 and not visited[x+1]:
        visit.append((x+1, dis+1))

    if 0 <= x-1 <= 100000 and not visited[x-1]:
        visit.append((x-1, dis+1))

    if x < k and 0 <= x*2 <= 100000 and not visited[x*2]:
        visit.append((x*2, dis))

print(ans_dis)
