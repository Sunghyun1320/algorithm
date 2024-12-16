import sys
sys.stdin = open("input.txt")
#############################################
def check_area(dir, xi, yi, xj, yj):
    if dir == 0:
        return True if yj > yi else False
    if dir == 1:
        return True if yj < yi else False
    if dir == 2:
        return True if xj < xi else False
    if dir == 3:
        return True if xj > xi else False


#############################################
def cal_time(diri, dirj, xi, yi, xj, yj):
    if (diri, dirj) in [(0, 1), (1, 0)]:
        if xi != xj:
            return False

        return abs(yi - yj) / 2

    if (diri, dirj) in [(2, 3), (3, 2)]:
        if yi != yj:
            return False

        return abs(xi - xj) / 2

    if abs(xi - xj) != abs(yi - yj):
        return False

    return abs(xi - xj)


#############################################
import heapq

dx = [0, 0, -1, 1]
dy = [1, -1, 0, 0]
#############################################
T = int(input())

for test_case in range(1, T+1):
    n = int(input())

    atm = [list(map(int, input().split())) + [0] for _ in range(n)]

    answer = 0

    heap = []

    for i in range(n):
        xi, yi, diri, _, _ = atm[i]
        for j in range(i+1, n):
            xj, yj, dirj, _, _ = atm[j]

            if diri == dirj:
                continue

            if not check_area(diri, xi, yi, xj, yj):
                continue

            if not check_area(dirj, xj, yj, xi, yi):
                continue

            time = cal_time(diri, dirj, xi, yi, xj, yj)

            if time is False:
                continue

            heapq.heappush(heap, [time, i, j])


    answer = 0
    while heap:
        time, a, b = heapq.heappop(heap)

        if atm[a][4] == 0 and atm[b][4] == 0:
            answer += atm[a][3]
            answer += atm[b][3]
            atm[a][4] = time
            atm[b][4] = time
            continue

        if atm[a][4] != 0 and atm[b][4] != 0:
            continue

        if atm[a][4] == 0 and atm[b][4] == time:
            answer += atm[a][3]
            atm[a][4] = time
            continue

        if atm[a][4] == time and atm[b][4] == 0:
            answer += atm[b][3]
            atm[b][4] = time
            continue


    print(f"#{test_case} {answer}")






