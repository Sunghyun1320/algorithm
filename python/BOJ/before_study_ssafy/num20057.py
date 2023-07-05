import sys
input = sys.stdin.readline
########################################################
# 데이터 입력 받기
# n은 홀수
n = int(input())

sand_graph = []

for _ in range(n):
    sand_graph.append(list(map(int, input().split())))

########################################################
# 모래 격자 회전하기
def turn_cw(graph):
    new_graph = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            new_graph[i][j] = graph[n - j - 1][i]

    return new_graph

########################################################
# 모래 확산
def deffusion_sand(x):
    global outside_sand

    sand = sand_graph[x[0]][x[1] - 1]
    if sand == 0:
        return
    sand_graph[x[0]][x[1] - 1] = 0

    # 1%확산 위치
    # 범위 이내이면 모래량 추가
    if 0 <= x[0] - 1 < n and 0 <= x[1] < n:
        sand_graph[x[0] - 1][x[1]] += (sand * 1) // 100
    # 아니면 밖으로 나간 모래량에 추가
    else:
        outside_sand += (sand * 1) // 100

    if 0 <= x[0] + 1 < n and 0 <= x[1] < n:
        sand_graph[x[0] + 1][x[1]] += (sand * 1) // 100
    else:
        outside_sand += (sand * 1) // 100

    # 7%확산 위치
    if 0 <= x[0] - 1 < n and 0 <= x[1] - 1 < n:
        sand_graph[x[0] - 1][x[1] - 1] += (sand * 7) // 100
    else:
        outside_sand += (sand * 7) // 100

    if 0 <= x[0] + 1 < n and 0 <= x[1] - 1 < n:
        sand_graph[x[0] + 1][x[1] - 1] += (sand * 7) // 100
    else:
        outside_sand += (sand * 7) // 100

    # 2%확산 위치
    if 0 <= x[0] - 2 < n and 0 <= x[1] - 1 < n:
        sand_graph[x[0] - 2][x[1] - 1] += (sand * 2) // 100
    else:
        outside_sand += (sand * 2) // 100

    if 0 <= x[0] + 2 < n and 0 <= x[1] - 1 < n:
        sand_graph[x[0] + 2][x[1] - 1] += (sand * 2) // 100
    else:
        outside_sand += (sand * 2) // 100

    # 10%확산 위치
    if 0 <= x[0] + 1 < n and 0 <= x[1] - 2 < n:
        sand_graph[x[0] + 1][x[1] - 2] += (sand * 10) // 100
    else:
        outside_sand += (sand * 10) // 100

    if 0 <= x[0] - 1 < n and 0 <= x[1] - 2 < n:
        sand_graph[x[0] - 1][x[1] - 2] += (sand * 10) // 100
    else:
        outside_sand += (sand * 10) // 100

    # 5%확산 위치
    if 0 <= x[0] < n and 0 <= x[1] - 3 < n:
        sand_graph[x[0]][x[1] - 3] += (sand * 5) // 100
    else:
        outside_sand += (sand * 5) // 100

    new_sand = sand
    new_sand -= (sand * 1) // 100
    new_sand -= (sand * 1) // 100
    new_sand -= (sand * 7) // 100
    new_sand -= (sand * 7) // 100
    new_sand -= (sand * 2) // 100
    new_sand -= (sand * 2) // 100
    new_sand -= (sand * 10) // 100
    new_sand -= (sand * 10) // 100
    new_sand -= (sand * 5) // 100

    #알파 위치
    if 0 <= x[0] < n and 0 <= x[1] - 2 < n:
        sand_graph[x[0]][x[1] - 2] += new_sand
    else:
        outside_sand += new_sand


########################################################
# 연산 수행
outside_sand = 0
strom_postion = [n // 2, n // 2]
for i in range(1, n):
    for _ in range(2):
        for __ in range(i):
            deffusion_sand(strom_postion)
            strom_postion[1] -= 1
        sand_graph = turn_cw(sand_graph)
        strom_postion[0], strom_postion[1] = strom_postion[1], n - 1 - strom_postion[0]

for __ in range(n - 1):
    deffusion_sand(strom_postion)
    strom_postion[1] -= 1


print(outside_sand)
