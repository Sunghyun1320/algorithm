import sys
input = sys.stdin.readline
###################################################
# 2개의 좌표를 입력받아 거리를 반환하는 함수
def cal_dis(position_a, position_b):
    x_a, y_a = position_a
    x_b, y_b = position_b

    dx = x_a - x_b
    dy = y_a - y_b
    return (dx ** 2 + dy ** 2) ** 0.5


###################################################
# a노드의 루트노드를 찾는 함수
def find(a):
    if arr[a] != a:
        arr[a] = find(arr[a])

    return arr[a]


###################################################
# a노드와 b노드가 다른 그래프이면 합치고 True반환
# 같은 그래프이면 따로 처리 안하고 False반환
def union(a, b):
    a = find(a)
    b = find(b)

    if a == b:
        return False

    if a > b:
        arr[a] = b
        return True

    if a < b:
        arr[b] = a
        return True


###################################################
# 별의 개수 받기
n = int(input())

# 별들 받아오기
star = [list(map(float, input().split())) for _ in range(n)]

# 별 2개와 그 거리를 저장하는 리스트
distance = []
for i in range(n):
    for j in range(i+1, n):
        distance.append([i, j, cal_dis(star[i], star[j])])

# 거리를 기준으로 정렬
distance.sort(key=lambda x: x[2])

# 부모노드를 저장하는 리스트
arr = [i for i in range(n)]

# 비용
sum_cost = 0

# 모든 거리들에 대해서
for a, b, cost in distance:
    # 다른 그래프이면 합치고, 현재 경로를 sum_cost에 저장
    if union(a, b):
        sum_cost += cost

# 소수 2째자리까지 반올림 후에 출력
print(round(sum_cost, 2))

