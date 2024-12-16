import sys
input = sys.stdin.readline
###########################################
dx = [0, -1, 0, 1]
dy = [-1, 0, 1, 0]
###########################################
def first_masic():
    global n, arr, fish, arr_n, arr_m
    # 최초 호출시 첫번째 마법으로 만들어진 행렬을 만드는 부분
    if n is None:
        n = 1
        while True:
            if n ** 2 >= N:
                break
            n += 1

        if N != n ** 2:
            n -= 1
            if N - n ** 2 == n:
                arr = [[None for _ in range(n)] for _ in range(n + 1)]
                arr_n = n + 1
                arr_m = n
            elif N - n**2 - n > 0:
                arr = [[None for _ in range(N - n**2)] for _ in range(n+1)]
                arr_n = n+1
                arr_m = N - n**2

            elif N - n**2 - n < 0:
                arr = [[None for _ in range(n + N - n ** 2)] for _ in range(n)]
                arr_n = n
                arr_m = N - n ** 2 + n


        else:
            arr = [[None for _ in range(n)] for _ in range(n)]
            arr_n = n
            arr_m = n

        i = N
        x = arr_n - 1
        y = arr_m
        dir = 0

        if n ** 2 != N:
            x = arr_n - 1
            y = arr_m

            for i in range(N-1, -1, -1):
                x += dx[dir]
                y += dy[dir]

                arr[x][y] = i

                nx = x + dx[dir]
                ny = y + dy[dir]

                if nx < 0 or nx >= arr_n or ny < 0 or ny >= arr_m:
                    dir = (dir + 1) % 4
                    break

        for j in range(i-1, -1, -1):
            x += dx[dir]
            y += dy[dir]

            arr[x][y] = j

            nx = x + dx[dir]
            ny = y + dy[dir]

            if N != n ** 2:
                if nx < 0 or nx >= arr_n - 1 or ny < 0 or ny >= n or arr[nx][ny] is not None:
                    dir = (dir + 1) % 4
            else:
                if nx < 0 or nx >= n or ny < 0 or ny >= n or arr[nx][ny] is not None:
                    dir = (dir + 1) % 4

###########################################
    new_arr = fish.copy()

    if N != n ** 2:
        for i in range(arr_n):
            for j in range(arr_m):
                if arr[i][j] is None:
                    continue
                for dir in range(4):
                    nx = i + dx[dir]
                    ny = j + dy[dir]

                    if nx < 0 or nx >= arr_n or ny < 0 or ny >= arr_m or arr[nx][ny] is None:
                        continue

                    if fish[arr[i][j]] - fish[arr[nx][ny]] >= 5:
                        new_arr[arr[i][j]] -= (fish[arr[i][j]] - fish[arr[nx][ny]]) // 5
                        new_arr[arr[nx][ny]] += (fish[arr[i][j]] - fish[arr[nx][ny]]) // 5

    else:
        for j in range(n):
            for i in range(n):
                for dir in range(4):
                    nx = i + dx[dir]
                    ny = j + dy[dir]

                    if nx < 0 or nx >= n or ny < 0 or ny >= n:
                        continue

                    if fish[arr[i][j]] - fish[arr[nx][ny]] >= 5:
                        new_arr[arr[i][j]] -= (fish[arr[i][j]] - fish[arr[nx][ny]]) // 5
                        new_arr[arr[nx][ny]] += (fish[arr[i][j]] - fish[arr[nx][ny]]) // 5

    return_arr = []
    if N != n ** 2:
        for j in range(arr_m):
            for i in range(arr_n - 1, -1, -1):
                if arr[i][j] is None:
                    continue

                return_arr.append(new_arr[arr[i][j]])
    else:
        for j in range(n):
            for i in range(n-1, -1, -1):
                return_arr.append(new_arr[arr[i][j]])

    return return_arr


###########################################
def second_masic():
    global arr_2
    if arr_2 is None:
        arr_2 = [[0 for _ in range(N // 4)] for _ in range(4)]

        nN = 0
        for i in range(N//4-1, -1, -1):
            arr_2[2][i] = nN
            nN += 1
        for i in range(N//4):
            arr_2[1][i] = nN
            nN += 1
        for i in range(N//4-1, -1, -1):
            arr_2[0][i] = nN
            nN += 1
        for i in range(N//4):
            arr_2[3][i] = nN
            nN += 1

    new_arr = fish.copy()

    for i in range(4):
        for j in range(N//4):
            for dir in range(4):
                nx = i + dx[dir]
                ny = j + dy[dir]

                if nx < 0 or nx >= 4 or ny < 0 or ny >= N//4:
                    continue

                if fish[arr_2[i][j]] - fish[arr_2[nx][ny]] >= 5:
                    new_arr[arr_2[i][j]] -= (fish[arr_2[i][j]] - fish[arr_2[nx][ny]]) // 5
                    new_arr[arr_2[nx][ny]] += (fish[arr_2[i][j]] - fish[arr_2[nx][ny]]) // 5

    return_arr = []
    for j in range(N//4):
        for i in range(3, -1, -1):
            return_arr.append(new_arr[arr_2[i][j]])

    return return_arr


###########################################
N, K = map(int, input().split())

n = None
arr = None
arr_n = 0
arr_m = 0

arr_2 = None
fish = list(map(int, input().split()))

count = 0
while True:
    min_fish = 10001
    max_fish = 0

    min_fish_list = []
    for i in range(N):
        if fish[i] < min_fish:
            min_fish = fish[i]
            min_fish_list = [i]

        elif fish[i] == min_fish:
            min_fish_list.append(i)

        max_fish = max(max_fish, fish[i])

    if max_fish - min_fish <= K:
        break

    for i in min_fish_list:
        fish[i] += 1

    fish = first_masic()
    fish = second_masic()
    count += 1

print(count)
###########################################
# K = 0
# fish = [5, 2, 3, 14, 9, 2, 11, 8]
# for N in range(4, 100, 4):
#     n = None
#     arr = None
#     first_masic()
#     print(N)
#     for j in arr:
#         print(j)
#
#     print("#########################################")