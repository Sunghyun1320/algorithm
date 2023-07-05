import sys
input = sys.stdin.readline
#############################################
INF = int(1e9)

n = int(input())
m = int(input())

# 플로이드 워셜용 전체 거리
distance = [[INF for _ in range(n+1)] for _ in range(n+1)]

# 자기 자신까지 거리는 0 처리
for i in range(n+1):
    distance[i][i] = 0

# 입력받는 관계에 따라 거리 갱신하기
for _ in range(m):
    a, b = map(int, input().split())

    distance[a][b] = 1
    distance[b][a] = 1

# 플로이드 워셜 시작
for i in range(1, n+1):
    for j in range(1, n+1):
        for k in range(1, n+1):
            distance[j][k] = min(distance[j][k], distance[j][i] + distance[i][k])

# 그룹에 속했는지 체크하는 리스트
check = [False for _ in range(n+1)]
# 각 대표를 저장하는 리스트
answer = []

# 불가능한 거리는 -1로 처리
for i in range(n+1):
    for j in range(n+1):
        if distance[i][j] == INF:
            distance[i][j] = -1


# 그룹에 속했는지 체크하는 리스트
check = [False for _ in range(n+1)]
# 각 대표를 저장하는 리스트
answer = []
# 각 사람을 체크하되
for i in range(1, n+1):
    # 그룹에 포함된 사람은 체크 안함
    if check[i]:
        continue

    # 새로운 그룹 만들기
    check[i] = True
    group = [i]
    min_cost = INF
    min_index = -1

    # 같은 그룹 사람 모두 더하기
    for j in range(1, n+1):
        if distance[i][j] > 0:
            group.append(j)
            check[j] = True

    # 같은 그룹에 있는 사람들의 소통시간의 최대값을 비교
    # 최소값 갱신
    for j in group:
        temp = max(distance[j])
        if min_cost > temp:
            min_cost = temp
            min_index = j

    # 대표 추가
    answer.append(min_index)

# 대표의 크기 = 위원회 개수
print(len(answer))
# 작은 수 부터 출력
answer.sort()
for i in answer:
    print(i)





