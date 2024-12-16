# 임의의 칸에 짝수번째로 도착하는 경우
# 임의의 칸에 홀수번째로 도착하는 경우
# 2가지 모두 가능할 수도 있다.
# 고르 2가지 경우가 모두 해당한다면 해당 시간 이후로 도착하는 모든 동생과 만날 수 있다.

import sys
from collections import deque
input = sys.stdin.readline
############################################
n, k = map(int, input().split())

visited = [[-1 for _ in range(500001)] for _ in range(2)]
visited[0][n] = 0
visited[1][n] = -1

visit = deque()
visit.append((n, 0,))

# 모든칸에 홀,짝을 구분해서 최소횟수로 도달
while visit:
    x, dis = visit.popleft()

    # 현재 장소에서 이동가능하고, 다음 거리의 홀짝으로 방문하지 않은 모든 칸 추가
    if 0 <= x+1 <= 500000 and visited[(dis+1) % 2][x+1] == -1:
        visited[(dis+1) % 2][x+1] = dis + 1
        visit.append((x+1, dis+1))

    if 0 <= x-1 <= 500000 and visited[(dis+1) % 2][x-1] == -1:
        visited[(dis+1) % 2][x - 1] = dis + 1
        visit.append((x-1, dis+1))

    if 0 <= x*2 <= 500000 and visited[(dis+1) % 2][x*2] == -1:
        visited[(dis+1) % 2][x * 2] = dis + 1
        visit.append((x*2, dis+1))

# print(visited[0][500000], visited[1][500000])

# 시간이 지난후에
for i in range(1001):
    position = k + ((i**2 + i) // 2)
    # 동생이 범위를 벗어나면 -1출력
    if position > 500000:
        print(-1)
        break

    # 해당칸에 동생보다 언니가 먼저 도착했고, 시간이 홀 or 짝으로 같다면 시간 출력
    if i - visited[0][position] >= 0 and (i - visited[0][position]) % 2 == 0:
        print(i)
        break

    if i - visited[1][position] >= 0 and (i - visited[1][position]) % 2 == 0:
        print(i)
        break


